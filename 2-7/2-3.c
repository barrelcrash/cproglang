#include <stdio.h>

#define MAX 10000

int isValidHex(char c);
int htoi(char s[]);

int main() {

  char test[MAX] = "0x20";
  char test2[MAX] = "0X0f";
  
  printf("%d\n", htoi(test));
  printf("%d\n", htoi(test2));

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

  int result = 0;

  if (s[0] = '0' && (s[1] == 'x' || s[1] == 'X')) {
    if (isValidHex(s[2]) && isValidHex(s[3])) {
      // convert chars to their hex-equivalent int value
      // "ones"
      int first = s[3] - '0';
      printf("first: %d\n", first);
      if (first > 9) {
        first = s[3] - 'A' + 10;
        if (first > 15) {
          first = s[3] - 'a' + 10;
        }
      }
      result += first;

      // "tens"
      int second = s[2] - '0';
      printf("second: %d\n", second);
      if (second > 9) {
        second = s[2] - 'A' + 10;
        if (second > 15) {
          second = s[2] - 'a' + 10;
        }
      }
      result += (second * 16);
    }
  }

  return result;
}

