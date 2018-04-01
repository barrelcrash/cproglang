/*
 * Write the function itob(n,s,b) that converts the integer n
 * into a base b character representation in the string s. In
 * particular, itob(n,s,16) formats n as a hexidecimal integer
 * in s.
 */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000

void itob(int n, char s[], int b);
void printitob(int n, int b);
void reverse(char s[]);

int main() {

  printitob(11, 10); // decimal

  printitob(11, 2); // binary

  printitob(11, 16); // hex
  printitob(123, 16);
  printitob(56, 16);
  printitob(543987, 16);

  return 0;
}

void printitob(int n, int b) {
  char target[MAX];

  for (int i = 0; i < sizeof(target); i++)
    target[i] = 0;

  itob(n, target, b);
  printf(target);
  printf("\n");
}

// itoa: convert n to characters in s
void itob(int n, char s[], int b) {
  int i, sign;

  unsigned int n2 = n;

  if ((sign = n) < 0)
    n2 = -n;

  i = 0;
  do {
    /* printf("%d\n", n2 % b); */
    int prop = n2 % b + '0';
    if (prop > '9') {
      s[i++] = prop + ('a' - ('9' + 1));
    } else {
      s[i++] = prop;
    }
  } while ((n2 /= b) > 0);
  if (sign < 0)
    s[i++] = '-';
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
