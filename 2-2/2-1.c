#include <stdio.h>
#include <limits.h>

main() {

  // TODO: figure out how to compute mins/maxes!

  // char
  printf("char min, max (header): %d, %d\n", CHAR_MIN, CHAR_MAX);
  printf("unsigned char max (header): %d\n", UCHAR_MAX);
  
  // short
  printf("short min, max (header): %d, %d\n", SHRT_MIN, SHRT_MAX);
  printf("unsigned short max (header): %d\n", USHRT_MAX);

  // int
  printf("int min, max (header): %d, %d\n", INT_MIN, INT_MAX);
  printf("unsigned int max (header): %d\n", UINT_MAX);

  // long
  printf("long min, max (header): %d, %d\n", LONG_MIN, LONG_MAX);
  printf("unsigned long max (header): %d\n", ULONG_MAX);
}
