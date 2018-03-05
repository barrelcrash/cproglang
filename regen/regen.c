/*
 * regen
 *
 * generate strings using regex-like
 * patterns.
 */

#include <stdio.h>

int main(int argc, char *argv[]) {

  int opt;

  // option flags
  while (--argc > 0 && (*++argv)[0] == '-') {
    while (opt = *++argv[0]) {
      switch (opt) {
        case 'x':
          printf("sample opt1 found\n");
          break;
        case 'y':
          printf("sample opt2 found\n");
          break;
      }
    }
  }

  // for now, just print the rule string
  printf(*argv);
}
