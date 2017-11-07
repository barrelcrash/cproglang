/*
 * In a two's complement number representation, our version of
 * itoa does not hand the largest negative number, that is, the
 * the value of n equal to -(2^wordsize-1). Explain why not.
 * Modify it to print that value correctly, regardless of the
 * machine on which it runs.
 */

/*
 * Explanation:
 *
 * "Two's complement is the way every computer I know of chooses
 * to represent integers. To get the two's complement negative
 * notation of an integer, you write out the number in binary.
 * You then invert the digits, and add one to the result."
 * - https://www.cs.cornell.edu/~tomf/notes/cps104/twoscomp.html
 *
 * Example:
 * 28:                   00011100
 * 28 inverted:          11100011 
 * add 1 for sign (-28): 11100100
 *
 * Additionally, we have the upper and lower bound of INT, which
 * is (not on this machine, but as an example) 127 and -128.
 * Meaning that when -128 is converted to the opposite sign, we
 * get 128, a number that cannot be represented by (signed) INT.
 * This implementation of itoa moreover reverses this number
 * and then subtracts one (opposite of above operation), resulting
 * in the initial value (10000000 > 01111111 > 10000000).
 *
 * The solution is to convert n to an unsigned int. Because this
 * int no longer has to accomodate negatives, we now have a
 * variable that can store a value above INT_MAX. The method
 * can then proceed as before.
 */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000

void itoa(int n, char s[]);
void printitoa(int n);
void reverse(char s[]);

int main() {
  printitoa(4);
  printitoa(-4);

  printitoa(INT_MIN);
}

void printitoa(int n) {
  char target[MAX];

  for (int i = 0; i < sizeof(target); i++)
    target[i] = 0;

  itoa(n, target);
  printf(target);
  printf("\n");
}

// itoa: convert n to characters in s
void itoa(int n, char s[]) {
  int i, sign;

  unsigned int n2;

  if ((sign = n) < 0)
    n2 = -n;

  i = 0;
  do {
    s[i++] = n2 % 10 + '0';
  } while ((n2 /= 10) > 0);
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
