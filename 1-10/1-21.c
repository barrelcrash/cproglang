#include <stdio.h>

#define MAX 1000

int getLine(char s[], int lim);

int main() {

  int len;
  int totalLen = 0;
  char line[MAX];
  char output[MAX * MAX];

  while ((len = getLine(line, MAX)) > 0) {
    totalLen += storeLine(line, len, output, totalLen);
  }

  printf(output);
}

int storeLine(char s[], int sLen, char o[], int totalLen) {
  int i;
  for (i = 0; i < sLen; i++, totalLen++) {
    o[totalLen] = s[i]; 
  }

  return i;
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
