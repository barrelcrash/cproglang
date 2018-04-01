#include <ctype.h>
#include <stdio.h>

#define BUFSIZE 100

int getch(void);
// int getint(int *); // what is the correct signature here?
void ungetch(int);

int main()
{
  int mpn;
  getint(&mpn);
  printf("%d \n", mpn);
}

// getint: get next integer from input into *pn
int getint(int *pn)
{
  int c, sign;

  while (isspace(c = getch())) // ignore preceding whitespace
    ;
  if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
    ungetch(c); // not a number
    return 0;
  }
  sign = (c == '-') ? -1 : 1;
  if (c == '+' || c == '-') // if sign, move to next
    c = getch(); 
  if (isdigit(c)) { // by now we should encounter a digit
    for (*pn = 0; isdigit(c); c = getch())
      *pn = 10 * *pn + (c - '0');
    *pn *= sign;
  }
  if (c != EOF) // no more digits, push last (non-digit) char back to input
    ungetch(c);
  return c;
}

char buf[BUFSIZE];
int bufp = 0;

int getch(void) // get a possibly pushed back character
{
  if (bufp > 0) {
    return buf[--bufp];
  } else {
    return getchar();
  }
}

void ungetch(int c) // push a character back on input
{
  if (bufp >= BUFSIZE)
    printf("ungetch: too many characters\n");
  else
    buf[bufp++] = c;
}
