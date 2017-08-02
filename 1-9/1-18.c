#include <stdio.h>

#define MAXLINE 1000
#define IN 1
#define OUT 0

int getline(char line[], int maxline);

main() {
  int len;
  char line[MAXLINE];

  while ((len = getline(line, MAXLINE)) > 0) {
    trimline(line); 
  }
}

int getLine(char line[], int maxline) {

  int c, i;

  for (i = 0; i < maxline - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
    line[i] = c;
  }

  if (c == '\n') {
    line[i] = c;
    i++;
  }

  return i;
}

void trimline(char line[]) {
  // check in-out of word and keep track of pos, length
  // if out is terminated by newline, subtract from pos by length
}
