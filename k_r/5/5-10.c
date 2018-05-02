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

int opcmp(char*, char[]);
int isvalidop(char*);

float fstack[MAX]; // input value stack
int fi = 0; // current free pos in fstack

int main(int argc, char *argv[]) {

  
  while (--argc > 0) {
    if (isdigit((*++argv)[0])) {
      *(fstack + fi++) = atof(*argv);
    } else {
      if (!isvalidop(*argv)) {
        printf("expr: character is not a digit or operand\n");
      } else {

        float top;
        float next;

        top = *(fstack + --fi);
        next = *(fstack + --fi);

        if (opcmp(*argv, "+")) {
          *(fstack + fi++) = top + next;
        } else if (opcmp(*argv, "-")) {
          *(fstack + fi++) = top - next;
        } else if (opcmp(*argv, "x")) {
          *(fstack + fi++) = top * next;
        } else if (opcmp(*argv, "/")) {
          *(fstack + fi++) = top / next;
        }
      }
    }
  }

  printf("expr result: %f\n", *(fstack + --fi));

  return 0;
}

int opcmp(char *argv, char *op) {
  return strcmp(argv, op) == 0;
}

int isvalidop(char *argv) {
  return opcmp(argv, "+")
          || opcmp(argv, "-")
          || opcmp(argv, "x")
          || opcmp(argv, "/");
}
