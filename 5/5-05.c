/* Write versions of strncpy, strncat, and strncmp,
 * which operate on at most the first n characters
 * of their argument strings. For example,
 * strncpy(s,t,n) copies at most n characters of t
 * to s.
 */

#include <stdio.h>

void astrcpy(char*, char*);
void astrncpy(char*, char*, int);

void nstrcat(char*, char*, int);

int astrcmp(char*, char*);
int astrncmp(char*, char*, int);

int main() {

  //astrncpy
  char cpy1[] = "hello\n";
  char cpy2[] = "zzzzz\n";
  astrncpy(cpy1, cpy2, 3);
  printf(cpy1); // should be "zzzlo"


  // astrncmp
  char cmp1[] = "abcdefg";
  char cmp2[] = "abcdxyz";
  printf("%d\n", astrcmp(cmp1, cmp2)); // should not be 0
  printf("%d\n", astrncmp(cmp1, cmp2, 4)); // should be 0
}

void astrcpy(char *s, char *t)
{
  while ((*s++ = *t++))
    ;
}

void astrncpy(char *s, char *t, int n)
{
  int nt = *t;
  while ((*s++ = *t++) && t - nt <= n)
    ;
}

void nstrcat(char *s, char *t, int n)
{
}

int astrcmp(char *s, char *t)
{
  for ( ; *s == *t; s++, t++)
    if (*s == '\0')
      return 0;
  return *s - *t;
}

int astrncmp(char *s, char *t, int n)
{
  int nt = *t;
  for ( ; *s == *t && t - nt <= n; s++, t++)
    if (*s == '\0')
      return 0;
  return *s - *t;
}
