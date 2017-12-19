#include <ctype.h>
#include <stdio.h>

#define BUFSIZE 100

int getch(void);
// int getint(int *); // what is the correct signature here?
void ungetch(int);

int main()
{
  int *pn;

  while(getint(*pn) != EOF)
    printf("%d\n", *pn);
}

// getint: get next integer from input into *pn
int getint(int *pn)
{
  int c, sign;

  while (isspace(c = getch()))
    ;
  if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
    ungetch(c); // not a number
    return 0;
  }
  sign = (c == '-') ? -1 : 1;
  if (c == '+' || c == '-')
    c = getch();
  for (*pn = 0; isdigit(c); c = getch())
    *pn = 10 * *pn + (c - '0');
  if (c != EOF)
    ungetch(c);
  return c;
}

char buf[BUFSIZE];
int bufp = 0;

int getch(void) // get a possibly pushed back character
{
  return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) // push a character back on input
{
  if (bufp >= BUFSIZE)
    printf("ungetch: too many characters\n");
  else
    buf[bufp++] = c;
}
