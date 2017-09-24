// write a function htoi(s), which converts a stirng of
// hexadecimal digits into its equivalent integer value

#include <stdio.h>
#include <math.h>

#define MAX 10000

int isValidHex(char c);
int htoi(char s[]);

int main() {

  char test[MAX] = "0x20";
  char test2[MAX] = "0X0f";
  char test3[MAX] = "0Xb79";

  printf("%d\n", htoi(test));
  printf("%d\n", htoi(test2));
  printf("%d\n", htoi(test3));

  return 0;
}

int isValidHex(char c) {
  char valid[] = "0123456789aAbBcCdDeEfF";

  for (int i = 0; valid[i] != '\0'; i++) {
    if (valid[i] == c)
      return 1;
  }

  return 0;
}

int htoi(char s[]) {

  // get length
  int len = 0;
  for (int i = 0; s[i] != '\0'; i++) {
    len++;
  }


  int result = 0;
  // first two must be 0X or 0x
  if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) {
    int last = len - 1;
    for (int j = last; j > 1; j--) {
      // convert chars to their hex-equivalent int value
      if (isValidHex(s[j])) {
        int value = s[j] - '0';
        if (value > 9) {
          value = s[j] - 'A' + 10;
          if (value > 15) {
            value = s[j] - 'a' + 10;
          }
        }
        result += (value * (pow(16, last - j)));
      }
    }
  }

  return result;
}
