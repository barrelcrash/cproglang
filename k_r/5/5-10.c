/*
 * Write the program expr, which evaluates a reverse Polish expression from
 * the command line, where each operator or operand is a separate argument.
 * For example,
 *    expr 2 3 4 + *
 * evaluates 2 x (3 + 4).
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000

float fstack[MAX]; // input value stack
int fi = 0; // current free pos in fstack

int main(int argc, char *argv[]) {

  
  while (--argc > 0) {
    if (isdigit((*++argv)[0])) {
      *(fstack + fi++) = atof(*argv);
    } else {
      if (strcmp(*argv, "+") != 0) {
        printf("expr: character is not a digit or operand\n");
      } else {

        float top;
        float next;

        top = *(fstack + --fi);
        next = *(fstack + --fi);

        if (strcmp(*argv, "+") == 0) {
          *(fstack + fi++) = top + next;
        }
      }
    }
  }

  printf("expr result: %f\n", *(fstack + --fi));

  return 0;
}

