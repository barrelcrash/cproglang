// Write the function `any(s1, s2)`, which returns the first location
// in the string s1 where any character from the string s2 occurs, or
// -1 if s1 contains no characters from s2;

#include <stdio.h>

int any(char s1[], char s2[]);

int main() {
  printf("%d\n", any("hello!", "lo")); // 2
  printf("%d\n", any("hello!", "xy")); // -1
}

int any(char s1[], char s2[]) {

  for (int i = 0; s1[i] != '\0'; i++) {
    for (int j = 0; s2[j] != '\0';j++) {
      if (s1[i] == s2[j]) {
        return i;
      }
    }
  }
  
  return -1;
}
