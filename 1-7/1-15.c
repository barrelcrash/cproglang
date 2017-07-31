#include <stdio.h>

/* print Fahrenheit-Celsius table using a function for conversion*/

double convertFahrToCels(int t);

main()
{
  int fahr;

  printf("Temperature Conversion Table\n");
  printf("----------------------------\n");
  for (fahr = 0; fahr <= 300; fahr = fahr + 20)
    printf("%3d %6.1f\n", fahr, convertFahrToCels(fahr));
}

double convertFahrToCels(int t)
{
  return (5.0/9.0) * (t - 32);
}
