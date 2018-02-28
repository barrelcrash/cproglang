/** includes **/

#include <ctype.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

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
  raw.c_cflag |= (CS8);
  raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN); // disable echo, canonical, Ctrl-Z, Ctrl-C
  raw.c_cc[VMIN] = 0;
  raw.c_cc[VTIME] = 1;

  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw); // set terminal attr
}

/** init **/

int main() {
  enableRawMode();

  while (1) {
    char c = '\0';
    if (read(STDIN_FILENO, &c, 1) == -1 && errno!= EAGAIN) die("read");
    if (iscntrl(c)) {
      printf("%d\r\n", c);
    } else {
      printf("%d ('%c')\r\n", c, c);
    }
    if (c == 'q')
      break;
  }
  return 0;
}
