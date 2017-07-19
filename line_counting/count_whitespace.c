#include <stdio.h>

main()
{
  int c, ws;

  ws = 0;
  while ((c = getchar()) != EOF) {
    if (c == '\n')
      ws++;

    if (c == ' ')
      ws++;

    if (c == '\n')
      ws++;
  }

  printf("whitespace: %d\n", ws);
}
