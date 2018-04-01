/**
* Replace tabs with a given number of spaces
*/
#include <stdio.h>

#define TABLEN 4

int main() {
    int len, c;
    char line[MAXLINE], final[MAXLINE * MAXLINE]; // program can handle 1mil chars

    while ((c = getchar()) != EOF) {
      if (c == '\t') {
        for (int i = 0; i < TABLEN; i++) {
          putchar(' ');
        }
      } else {
        putchar(c);
      }
    }

    return 0;
}
