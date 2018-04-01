/*
 * Write a version of itoa that accepts three arguments instead of
 * two. The third argument is a minimum field width; the converted
 * number must be padded with blanks on the left if necessary to
 * make it wide enough.
 */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000

void paditoa(int n, char s[], int w);
void printitoa(int n, int w);
void reverse(char s[]);

int main() {
  printitoa(4, 4);
  printitoa(-4, 3);

  printitoa(INT_MIN, 20);

  return 0;
}

void printitoa(int n, int w) {
  char target[MAX];

  for (int i = 0; i < sizeof(target); i++)
    target[i] = 0;

  paditoa(n, target, w);
  printf(target);
  printf("\n");
}

// paditoa: convert n to a minimum of w characters in s
void paditoa(int n, char s[], int w) {
  int i, sign;

  unsigned int n2 = n;

  if ((sign = n) < 0)
    n2 = -n;

  i = 0;
  do {
    s[i++] = n2 % 10 + '0'; // add ints as chars
  } while ((n2 /= 10) > 0);
  if (sign < 0)
    s[i++] = '-'; // apply sign
  if (i < w) {
    while (i < w)
      s[i++] = ' '; // pad
  }

  s[i] = '\0';
  reverse(s);
}

// reverse: reverse string s in place
void reverse(char s[]) {
  int c, i, j;

  for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}
