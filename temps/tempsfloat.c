#include <stdio.h>

/* print Fahrenheit-Celsius table
 * for fahr = 0, 20, ..., 300 */

main()
{
  float fahr, celsius;
  int lower, upper, step;

  lower = 0;    // lower limit of table
  upper = 300;  // uppper limit
  step = 20;    // step size

  fahr = lower;
  printf("%3s %6s\n", "FRH", "CLS");
  while (fahr <= upper) {
    celsius = (5.0/9.0) * (fahr - 32.0);
    printf("%3.0f %6.1f\n", fahr, celsius);
    fahr = fahr + step;
  }
}
 
