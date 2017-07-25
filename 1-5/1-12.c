#include <stdio.h>

#define IN  1
#define OUT 0

// print one word per line
main()
{
  int c, state;

  state = OUT;

  while ((c = getchar()) != EOF) {
    if (c == '\n' || c == ' ' || c == '\t') {
      if (state == IN) {
        putchar('\n');
      }
      state = OUT;
    } else if (state == OUT) {
      state = IN;
      putchar(c);
    } else {
      putchar(c);
    }
  }
}
