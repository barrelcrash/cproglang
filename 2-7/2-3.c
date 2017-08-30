#include <stdio.h>

#define MAX 10000

int isValidHex(char c);
int htoi(char s[]);

int main() {

  char test[MAX] = "0x01";
  char test2[MAX] = "0X02";
  
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

  if (s[0] = '0' && (s[1] == 'x' || s[i] == 'X')) {
    if (isValidHex(s[2] && s[3])) {
      // convert chars to their hex-equivalent int value
      // "ones"
      int first = s[3] - '0';
      if (first > 9) {
        first = s[3] - 'A' + 9;
        if (first > 14) {
          first = s[3] - 'a' + 9;
        }
      }

      result += first;
    }
  }

}
