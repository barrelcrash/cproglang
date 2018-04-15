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

int main(int argc, char *argv[]) {
  
  while (--argc > 0 && isdigit((*++argv)[0])) {

    int fl = atoi(*argv);

    printf("%d\n", fl);

  }
}
