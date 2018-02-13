// Rewrite appropriate programs from earlier chapters with
// pointers instead of array indexing.

#include <stdio.h>

int main() {

  char str1[] = "asdfjkl;";
  char str2[] = "fjkl";
  char str3[] = "qwerty";

  printf("%d\n", strindex(&str1, &str2)); // 3
  printf("%d\n", strindex(&str1, &str3)); // -1

}

// strindex
int strindex(char *s, char *t) {
  int i, j, k;

  // parens as *(s + i) are necessary here because we
  // are both using pointer arithmetic and deferencing
  // the value of the arithmetized pointer in the
  // same expression
  for (i = 0; *(s + i) != '\0'; i++) {
    for (j = i, k = 0; *(t + k) != '\0' && *(s + j) == *(t + k); j++, k++)
      ;
    if (k > 0 && *(t + k) == '\0')
      return i;
  }
  return -1;
}
