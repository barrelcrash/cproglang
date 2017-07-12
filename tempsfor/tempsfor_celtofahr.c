#include <stdio.h>

/* print Celsius-Farenheit table */
main()
{
  int cel;

  printf("Temperature Conversion Table\n");
  printf("----------------------------\n");
  for (cel = 0; cel <= 150; cel = cel + 10)
    printf("%3d %6.1f\n", cel, ((9.0/5.0) * cel) + 32);
}
