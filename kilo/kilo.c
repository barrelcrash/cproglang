/** includes **/

#include <ctype.h>
#include <errno.h>
#include <termios.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

/** defines **/

#define CTRL_KEY(k) ((k) & 0x1f)

/** data **/

struct editorConfig {
  int screenrows;
  int screencols;
  struct termios orig_termios;
};

struct editorConfig E;

/** terminal **/

void die(const char *s) {
  write(STDOUT_FILENO, "\x1b[2J", 4); // clear screen
  write(STDOUT_FILENO, "\x1b[H", 3); // put cursor at top, equiv. to [1;1H
  perror(s);
  exit(1);
}

void disableRawMode() {
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &E.orig_termios) == -1) // reset term attr
    die("tcsetattr");
}

void enableRawMode() {
  if (tcgetattr(STDIN_FILENO, &E.orig_termios) == -1) die("tcgetattr"); // move terminal attr to struct

  atexit(disableRawMode); // invoke this func at exit

  struct termios raw = E.orig_termios;
  // bit flipping
  raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON); // disable Ctrl-S, Ctrl-Q, Ctrl-M processing, misc
  raw.c_oflag &= ~(OPOST); // disable output post-processing
  raw.c_cflag |= (CS8); // set char byte len to 8
  raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN); // disable echo, canonical, Ctrl-Z, Ctrl-C
  raw.c_cc[VMIN] = 0; // min for read() to return
  raw.c_cc[VTIME] = 1; // interval for read() to return

  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw); // set terminal attr
}

char editorReadKey() {
  int nread; // save read return val here for error checking
  char c;
  while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
    if (nread == -1 && errno != EAGAIN) die("read");
  }
  return c;
}

int getCursorPosition(int *rows, int *cols) {
  char buf[32];
  unsigned int i = 0;

  if (write(STDOUT_FILENO, "\x1b[6n", 4) != 4) return -1;

  while (i < sizeof(buf) - 1) {
    if (read(STDIN_FILENO, &buf[i], 1) != 1) break;
    if (buf[i] == 'R') break;
    i++;
  }
  buf[i] = '\0';

  if (buf[0] != '\x1b' || buf[1] != '[') return -1;
  if (sscanf(&buf[2], "%d;%d", rows, cols) != 2) return -1;

  return 0;
}

// attempt to get window size from ioctl
int getWindowSize(int *rows, int *cols) {
  struct winsize ws;

  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
    // issue here - cursor does not make it to bottom-right corner
    // prepend 1 to above check to debug
    if (write(STDOUT_FILENO, "\x1b[999C\x1b[999B", 12 != 12)) return -1;
    return getCursorPosition(rows, cols);
  } else {
    *cols = ws.ws_col;
    *rows = ws.ws_row;
    return 0;
  }
}

/** append buffer **/

struct abuf {
  char *b;
  int len;
};

#define ABUF_INIT {NULL, 0} // abuf constructor

void abAppend(struct abuf *ab, const char *s, int len) {
  char *new = realloc(ab->b, ab->len + len);

  if (new == NULL) return;
  memcpy(&new[ab->len], s, len);
  ab->b = new;
  ab->len += len;
}

void abFree(struct abuf *ab) {
  free(ab->b);
}

/** output **/
void editorDrawsRows(struct abuf *ab) {
  int y;
  for (y = 0; y < E.screenrows; y++) {
    abAppend(ab, "~", 1);

    // we don't want ot add return on the last row
    if (y < E.screenrows - 1) {
      abAppend(ab, "\r\n", 2);
    }
  }
}

void editorRefreshScreen() {
  struct abuf ab = ABUF_INIT;

  abAppend(&ab, "\x1b[2J", 4); // clear screen
  abAppend(&ab, "\x1b[H", 3); // put cursor at top, equiv. to [1;1H

  editorDrawsRows(&ab);

  abAppend(&ab, "\x1b[H", 3); // put cursor at top, equiv. to [1;1H

  write(STDOUT_FILENO, ab.b, ab.len);
  abFree(&ab);
}

/** input **/

void editorProcessKeypress() {
  char c = editorReadKey();

  switch (c) {
    case CTRL_KEY('q'):
      write(STDOUT_FILENO, "\x1b[2J", 4); // clear screen
      write(STDOUT_FILENO, "\x1b[H", 3); // put cursor at top, equiv. to [1;1H
      exit(0);
      break;
  }
}

/** init **/

void initEditor() {
  if (getWindowSize(&E.screenrows, &E.screencols) == -1) die("getWindowSize");
}

int main() {
  enableRawMode();
  initEditor();

  while (1) {
    editorRefreshScreen();
    editorProcessKeypress();
  }
  return 0;
}
