#include <ctype.h>
#include <stdio.h>

#define BUFSIZE 100

int getch(void);
int getDivisor(int);
// int getfloat(int *); // what is the correct signature here?
void ungetch(int);

int main()
{
  float mpn;
  getfloat(&mpn);
  printf("%f \n", mpn);
}

// getfloat: get next float from input into *pn
int getfloat(float *pn)
{
  int i, c, sign, saw, diff;

  while (isspace(c = getch())) // ignore preceding whitespace
    ;

  if (!isdigit(c)
      && c != EOF
      && c != '+'
      && c != '-'
      && c != '.') {
    ungetch(c); // not a number
    return 0;
  }

  sign = (c == '-') ? -1 : 1;

  if (c == '+' || c == '-') // if sign, move to next
    c = getch(); 

  saw = 0; // keep track of where the decimal is

  if (isdigit(c) || c == '.') { // by now we should encounter a digit
    for (i = 0, *pn = 0;
          isdigit(c) || (c == '.' && saw == 0);
          c = getch(), i++) {
      if (c == '.') {
        saw = i; // found our decimal, record it
        continue;
      }
      *pn = 10 * *pn + (c - '0');
    }
    diff = saw > 0 ? (i - 1) - saw : 0; // distance of decimal from last digit, contains offset :(
    *pn /= getDivisor(diff); // apply decimal
    *pn *= sign; // apply sign
  }

  if (c != EOF) // no more digits, push last (non-digit) char back to input
    ungetch(c);

  return c;
}

int getDivisor(int v)
{
  int divisor = 1;
  while (v-- > 0)
    divisor *= 10;
  return divisor;
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
