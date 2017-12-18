/*
 * Extend atof to handle scientific notation of the form 123.45e6
 * where a floating-point number may be followed by e or E and an
 * optionally signed exponent.
 */

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#define MAX 1000

double atof(char s[]);

int main() {
  printf("atof:\n");
  printf("%f\n", atof("45"));
  printf("%f\n", atof("-45"));
  printf("%f\n", atof("-45.045"));
  printf("%f\n", atof("4e5"));

  return 0;
}

double atof(char s[]) {
  double val, power;
  int i, sign, result;

  for (i = 0; isspace(s[i]); i++) // skip initial spaces
    ;

  sign = (s[i] == '-') ? -1 : 1; // save sign

  if (s[i] == '+' || s[i] == '-') // move past sign char
    i++;

  // get whole values
  for (val = 0.0; isdigit(s[i]); i++)
    val = 10.0 * val + (s[i] - '0');

  if (s[i] == '.')
    i++;

  // get fractional values,
  // keep track of decimal places
  for (power = 1.0; isdigit(s[i]); i++) {
    val = 10.0 * val + (s[i] - '0');
    power *= 10.0;
  }

  result = sign * val / power;

  // recurse for scientific exponent if indicated
  if (s[i] == 'e' || s[i] == 'E') {
    int j;
    char sub[MAX];

    i++;

    for (j = 0; j < strlen(s); j++)
      sub[j] = s[i + j];

    result = result * pow(10.0, atof(sub));
  }

  return result;
}
