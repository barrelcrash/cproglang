/** includes **/

#include <ctype.h>
#include <errno.h>
#include <termios.h>
#include <stdlib.h>
#include <stdio.h>
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

int getWindowSize(int *rows, int *cols) {
  struct winsize ws;

  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
    return -1;
  } else {
    *cols = ws.ws_col;
    *rows = ws.ws_row;
    return 0;
  }
}

/** output **/

void editorDrawsRows() {
  int y;
  for (y = 0; y < E.screenrows; y++) {
    write(STDOUT_FILENO, "~\r\n", 3);
  }
}

void editorRefreshScreen() {
  write(STDOUT_FILENO, "\x1b[2J", 4); // clear screen
  write(STDOUT_FILENO, "\x1b[H", 3); // put cursor at top, equiv. to [1;1H
  editorDrawsRows();
  write(STDOUT_FILENO, "\x1b[H", 3); // put cursor at top, equiv. to [1;1H
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
