/* Write the function strend(s,t), which returns 1
 * if the string t occurs at the end of the string
 * s, and zero otherwise.
 */

#include <stdio.h>

int strend(char*, char*);

int main()
{
  printf("%d\n", strend("hello", "lo")); // should be 1
  printf("%d\n", strend("hloello", "lo")); // should be 1
  printf("%d\n", strend("hello", "wo")); // should be 0
  printf("%d\n", strend("hello", "ll")); // should be 0
  printf("%d\n", strend("hello", "lolo")); // should be 0
  printf("%d\n", strend("hello", "ww")); // should be 0
  return 0;
}

int strend(char *s, char *t)
{
  char *tr;
  while (*s++) {
    tr = t; // note where t is
    while (*s++ == *t++) {
      if (*t == '\0')
        return 1; // the end of t (implicitly end of s), we have a match
    }
    t = tr; // didn't match at end, reset t
  }
  return 0; // no match
}
