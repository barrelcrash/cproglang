/*
 * Write the function strrindex(s,t), which returns the position
 * of the rightmost occurrence of t in s, or -1 if there is
 * none.
 */

#include <stdio.h>
#include <string.h>

int strrindex(char s[], int t);

int main() {

  printf("%d\n", strrindex("", 'a'));
  printf("%d\n", strrindex("happy", 'a'));
  printf("%d\n", strrindex("happy birthday", 'a'));

  return 0;
}

int strrindex(char s[], int t) {
  int found, i;

  found = -1;

  for (i = 0; i < strlen(s); i++) {
    if (s[i] == t) {
      found = i;
    }
  }

  return found;
}
