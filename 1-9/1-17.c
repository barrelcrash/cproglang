#include <stdio.h>

/* print all input lines that are longer than 80 characters */

#define LINE_MAX 1000
#define LINE_MIN 80

int getLine(char s[], int lim);

main() {
  int target;
  char line[LINE_MAX];

}

int getLine(char s[], int lim) {

  int c, i;

  for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
    s[i] = c;
  }
}
