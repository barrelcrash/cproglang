/** includes **/

#include <ctype.h>
#include <errno.h>
#include <termios.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/** defines **/

#define CTRL_KEY(k) ((k) & 0x1f)

/** data **/

struct termios orig_termios;

/** terminal **/

void die(const char *s) {
  perror(s);
  exit(1);
}

void disableRawMode() {
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1) // reset term attr
    die("tcsetattr");
}

void enableRawMode() {
  if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) die("tcgetattr"); // move terminal attr to struct

  atexit(disableRawMode); // invoke this func at exit

  struct termios raw = orig_termios;
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

/** output **/

void editorRefreshScreen() {
  write(STDOUT_FILENO, "\x1b[2J", 4);
}

/** input **/

void editorProcessKeypress() {
  char c = editorReadKey();

  switch (c) {
    case CTRL_KEY('q'):
      exit(0);
      break;
  }
}

/** init **/

int main() {
  enableRawMode();

  while (1) {
    editorRefreshScreen();
    editorProcessKeypress();
  }
  return 0;
}
