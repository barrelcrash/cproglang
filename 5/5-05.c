/* Write versions of strncpy, strncat, and strncmp,
 * which operate on at most the first n characters
 * of their argument strings. For example,
 * strncpy(s,t,n) copies at most n characters of t
 * to s.
 */

#include <stdio.h>

void astrcpy(char*, char*);
void astrncpy(char*, char*, int);

void astrcat(char*, char*);
void astrncat(char*, char*, int);

int astrcmp(char*, char*);
int astrncmp(char*, char*, int);

int main() {

  //astrncpy
  char cpy1[] = "hello\n";
  char cpy2[] = "uv1234\n";
  astrncpy(cpy1, cpy2, 3);
  printf(cpy1); // should be "uv1lo"

  putchar('\n');

  // astrncat
  char cat1[] = "goodbye";
  char cat2[] = "hijklmn";
  astrncat(cat1, cat2, 3);
  printf(cat1); // should be "goodbyehij"

  putchar('\n');

  // astrncmp
  char cmp1[] = "abcdefg";
  char cmp2[] = "abcdxyz";
  printf("%d\n", astrcmp(cmp1, cmp2)); // should not be 0
  printf("%d\n", astrncmp(cmp1, cmp2, 4)); // should be 0
  printf("%d\n", astrncmp(cmp1, cmp2, 5)); // should not be 0
}

void astrcpy(char *s, char *t)
{
  while ((*s++ = *t++))
    ;
}

void astrncpy(char *s, char *t, int n)
{
  char *nt = t;
  while ((*s++ = *t++) && t - nt < n)
    ;
}

void astrcat(char *s, char *t)
{
  while ((*s))
    *s++;
  while ((*s++ = *t++))
    ;
}

void astrncat(char *s, char *t, int n)
{
  while ((*s))
    *s++;

  char *nt = t;
  while ((*s++ = *t++) && t - nt < n)
    ;
  *s = '\0';
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
  char *nt = t;
  for ( ; *s == *t && t - nt < n; s++, t++) {
    if ((*s == '\0') || (t - nt + 1 == n)) {
      return 0;
    }
  }
  return *s - *t;
}
