#include <ctype.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

struct termios orig_termios;

void disableRawMode() {
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios); // reset term attr
}

void enableRawMode() {
  tcgetattr(STDIN_FILENO, &orig_termios); // move terminal attr to struct

  atexit(disableRawMode); // invoke this func at exit

  struct termios raw = orig_termios;
  raw.c_lflag &= ~(ECHO | ICANON); // bit-flipping, turn off echo & canonical
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw); // set terminal attr
}

int main() {
  enableRawMode();

  char c;
  while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q') {
    if (iscntrl(c)) {
      printf("%d\n", c);
    } else {
      printf("%d ('%c')\n", c, c);
    }
  }
  return 0;
}
