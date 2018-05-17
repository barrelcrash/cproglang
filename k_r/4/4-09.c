/* this program forms the basis on which exercises 4-3 through 4-10 build */

// Our getch and ungetch do not handle a pushed-back EOF
// correctly. Decide what their properties ought to be
// if an EOFis pushed back, then implement your design.
//
// Student note: The change required is changing
// the getch/ungetch buf to 'int', as 'char' cannot
// handle negative characters.

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h> /* for atof() - in K&R, math.h is referenced - this is an anachronism */

#define BUFSIZE 100
#define MAXOP 100 /* max size of operand or operator */
#define MAXVAL  100 /* maximum depth of val stack */
#define MAXVARS 26
#define NUMBER '0' /* signal that a number was found */

int getop(char []);
void push(double);
double pop(void);

double getTop(void);
void swapTop(void);
void clearStack(void);

int getch(void);
void ungetch(int);
void ungets(char[]);

int isVar(int);
int getVarValue(int);
void setVarValue(int, double);

/* reverse Polish calculator */
int main(void)
{
  int type;
  double op1, op2, r;
  char s[MAXOP];

  printf(
        "K&R'S POLISH CALCULATOR\n"
        "-----------------------\n"
        "Takes expressions in the notation:\n"
        "'4 5 +'\n"
        "\n"
        "Handles the following normal operators:\n"
        "+ - * / %%\n"
        "\n"
        "Handles the following special operators:\n"
        "^: power of\n"
        "$: sin of\n"
        "#: exponent of\n"
        "?: print most recent result\n"
        "@: duplicate most recent result\n"
        "~: swap two most recent results\n"
        "!: clear all results\n"
        ">: assign value to variable\n"
        "\n"
      );

  while((type = getop(s)) != EOF)
  {
    switch(type)
    {
      case NUMBER: // == 0
        push(atof(s));
        break;
      case '+':
        push(pop() + pop());
        break;
      case '*':
        push(pop() * pop());
        break;
      case '-':
        op2 = pop();
        push(pop() - op2);
        break;
      case '/':
        op2 = pop();
        if(op2 != 0.0)
          push(pop() / op2);
        else
          printf("divide error: zero divisor\n");
        break;
      case '%':
        op2 = pop();
        if (op2 != 0.0)
          push(fmod(pop(), op2));
        else
          printf("modulo error: zero divisor\n");
        break;
      case '^':
        op1 = pop();
        op2 = pop();
        if ((op1 == 0 && op2 < 0)
            || (op1 < 0 && !isdigit(op2))) {
          printf("pow error:  invalid expression");
        } else {
          push(pow(op1, op2));
        }
        break;
      case '$':
        push(sin(pop()));
        break;
      case '#':
        push(exp(pop()));
        break;
      case '?': // queries top of stack
        printf("current top: %f\n", getTop());
        break;
      case '@': // duplicates top value of stack
        push(getTop());
        break;
      case '~': // swaps top two numbers on stack
        swapTop();
        break;
      case '!':
        clearStack();
        break;
      case '>':
        r = pop();
        setVarValue(getop(s), r);
        push(r);
        break;
      case '\n':
        r = pop();
        setVarValue('p', r);
        printf("\t%.8g\n", r);
        break;
      default:
        if (isVar(type)) {
          push(getVarValue(type));
        } else {
          printf("error: unknown command %s\n", s);
        }
        break;
    }
  }

  return 0;
}


int sp = 0; /* next free stack position */
double val[MAXVAL]; /* value stack */

/* push: push f onto value stack */
void push(double f)
{
  if(sp < MAXVAL)
    val[sp++] = f;
  else
    printf("push error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void)
{
  if (sp > 0) {
    return val[--sp];
  } else {
    printf("pop error: stack empty\n");
    return 0.0;
  }
}

double getTop(void) {
  if (sp > 0) {
    return val[sp - 1];
  } else {
    printf("getTop error: stack empty\n");
    return 0.0;
  }
}

/* swapTop: swap top two items on stack */
void swapTop(void) {
  if (sp > 1) {
    double top = pop();
    double next = pop();
    push(top);
    push(next);
  } else {
    printf("swapTop error: not enough elements in stack");
  }
}

/* clearStack: clear the entire stack */
void clearStack(void) {
  sp = 0; // not safe!
}

/* getop: get next operator or numeric operand */
int getop(char s[])
{
  int i, c, sign;

  // skip ws
  while((s[0] = c = getch()) == ' ' || c == '\t')
    ;

  s[1] = '\0';
  if(!isdigit(c) && c != '.' && c != '-')
    return c; /* not a number */

  i = 0;
  if(c == '-') {
    if (isdigit(s[++i] = c = getch())) {
      while(isdigit(s[++i] = c = getch()))
        ;
    } else {
      ungetch(c);
      return '-';
    }
  }
  if(isdigit(c)) /* collect integer part */
    while(isdigit(s[++i] = c = getch()))
      ;
  if(c == '.')
    while(isdigit(s[++i] = c = getch()))
      ;
  s[i] = '\0';

  if(c != EOF)
    ungetch(c);
  return NUMBER;
}


/*
 * CHAR BUFFER
 */
int buf; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

int getch(void) /* get a (possibly pushed back) character */
{
  char temp = 0;
  if (buf != '\0') {
    temp = buf;
    buf = '\0';
  } else {
    temp = getchar();
  }
  return temp;
}

void ungetch(int c) /* push character back on input */
{
  if(buf != '\0')
    printf("ungetch: a character is already present in the buffer\n");
  else
    buf = c;
}

// -- push a string back onto input
// does not directly know about buf[],
// but does need to know about bufp for
// error handling
void ungets(char s[])
{
  int i;
  for (i = 0; s[i] !='\0'; i++) {
    if (bufp >= BUFSIZE)
      printf("ungets: too many characters\n");
    else
      ungetch(s[i]);
  }
}

/*
 * VARIABLES
 */
double varbuf[MAXVARS] = { 0.0 };

int isVar(int c)
{
  return (c >= 'a') && (c <= 'z');
}

void setVarValue(int c, double v)
{
  if (isVar(c)) {
    varbuf[c - 'a'] = v;
  } else {
    printf("setVarValue: not a character a-z\n");
  }
}

int getVarValue(int c)
{
  return varbuf[c - 'a'];
}
