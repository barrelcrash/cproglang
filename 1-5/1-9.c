#include <stdio.h>

main()
{
  int c, lastWS;

  lastWS = 0;

  while ((c = getchar()) != EOF) {
    if (c == ' ') {
      if (!lastWS) {
        putchar(c);
        lastWS = 1;
      }
    } else {
      putchar(c);
      lastWS = 0;
    }
  }
}
