/*
 * "write a program `entab` that replaces strings of blanks by
 * the minimum number of tabs and blanks to achieve the same
 * spacing."
 *
 * author: barrelcrash
 *
 * author's note: many solutions for this problem simply replace
 * a given tab's worth of whitespaces, as they are encountered,
 * with a tab, rather than keeping track of tabstop locations, 
 * adding a tab, and removing the appropriate amount of
 * whitespace. this solution does not handle mixed tabs and
 * spaces, but satisfies K&R's criteria as given
 */
#include <stdio.h>

#define MAX 1000
#define TABSTOP 4

void entab(char s[], int len);
int getLine(char s[], int lim);
int storeLine(char s[], int sLen, char o[], int totalLen);

int main() {

  int len;
  int totalLen = 0;
  char line[MAX];
  char output[MAX * MAX];

  while ((len = getLine(line, MAX)) > 0) {
    entab(line, len);
    totalLen += storeLine(line, len, output, totalLen);
  }

  printf("\n");
  printf("result: \n");
  printf(output);
}

void entab(char s[], int len) {

  int ws = 0; // track spaces
  int tabspace = 0; // track tab-occupied space

  for (int i = 0; i < len; i++) {
    int isTabStop = ((i + tabspace + 1) % TABSTOP) == 0;
    if (s[i] == ' ') {
      ws++;
    } else if (s[i] != ' ' && !isTabStop) {
      ws = 0;
    }

    if (isTabStop) {
      // if we arrive at a tabstop and more than one space, entab
      if (ws > 1) {
        i -= (ws - 1);
        s[i] = '\t';
        i++;
        tabspace += (ws - 1);

        for (int t = i; t < len; t++) {
          s[t] = s[t + (ws - 1)];
        }

        len -= ws - 1;
      }

      ws = s[i] == ' ' ? 1 : 0;
    }
  }
}

int storeLine(char s[], int sLen, char o[], int totalLen) {

  int i;

  for (i = 0; s[i] != '\0'; i++, totalLen++) {
    o[totalLen] = s[i]; 
  }

  return i;
}

int getLine(char s[], int lim) {

  int c, i;

  for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
    s[i] = c;
  }

  if (c == '\n') {
    s[i] = c;
    i++;
  }

  s[i] = '\0';

  return i;
}

