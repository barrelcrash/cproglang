/* 6-1: our version of getword does not properly handle
 * underscores, string constants, comments, or preprocessor
 * control lines. Write a better version.
 */

#include <ctype.h>
#include <stdio.h>

#define BUFSIZE 100
#define MAXWORD 100

int getword(char *, int);
int isvalidchar(int);

// TODO: finish keytab
struct key {
  char *word;
  int count;
} keytab[] = {
  "auto", 0,
  "break", 0,
  "case", 0
};

int main() {
  int n;
  char word[MAXWORD];

  while(getword(word, MAXWORD) !=EOF)
    if (isalpha(word[0]))
      if ((n = binsearch(word, keytab, NKEYS)) >= 0)
        keytab[n].count++;
  for (n = 0; n < NKEYS; n++)
    if (keytab[n].count > 0)
      printf("%4d %s\n",
          keytab[n].count, keytab[n].word);
  return 0;
}

// TODO: copy over binsearch

int getword(char *word, int lim) {
  int c, getch(void);
  void ungetch(int);
  char *w = word;

  while (isspace(c = getch()))
    ;
  if (c != EOF)
    *w++ = c;
  if (!isalpha(c)) {
    *w = '\0';
    return c;
  }
  for ( ; --lim > 0; w++)
    if (!isvalidchar(*w = getch())) {
      ungetch(*w);
      break;
    }
  *w = '\0';
  return word[0];
}

int isvalidchar(int c) {
  return isalnum(c) || c =='_';
}

/*
 * CHAR BUFFER
 */
char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

int getch(void) /* get a (possibly pushed back) character */
{
  return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
  if(bufp >= BUFSIZE)
    printf("ungetch: too many characters\n");
  else
    buf[bufp++] = c;
}
