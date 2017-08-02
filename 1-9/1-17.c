#include <stdio.h>

/* print all input lines that are longer than 80 characters */

#define LINE_MAX 1000
#define LINE_MIN 10

void storeLine(char s[], char t[], int currentChars);
int getLine(char s[], int lim);

main() {
  int len; // length of current line
  int currentChars; // total length of stored lines
  int i; // loop counter
  char line[LINE_MAX]; // current line
  char passedLines[LINE_MAX * 1000]; // stored lines

  currentChars = 0;

  while ((len = getLine(line, LINE_MAX)) > 0) {
    if (len > LINE_MIN) {
      storeLine(line, passedLines, currentChars);
      currentChars += len; // update total length
    }
  }

  i = 0;

  while (i <= currentChars) {
    putchar(passedLines[i]);
    i++;
  }

  return 0;
}

void storeLine(char s[], char t[], int currentChars) {

  int c, i, j;

  i = 0;
  j = currentChars;

  while ((c = s[i]) != '\0') {
    t[j] = s[i]; 
    i++;
    j++;
  }
}

int getLine(char s[], int lim) {

  int c, i;

  for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
    s[i] = c;
  }

  if (c == '\n') {
    s[i] = c;
    i++;
  }

  return i;
}
