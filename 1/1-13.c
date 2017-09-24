#include <stdio.h>

#define IN  1
#define OUT 0

// histogram of word lengths
main()
{
  int c, i, j, state, length;
  int lengths[10];

  length = 0;
  state = OUT;

  for (i = 0; i <= 9; i++) {
    lengths[i] = 0;
  }

  while ((c = getchar()) != EOF) {
    if (c == ' ' || c == '\n' || c == '\t') {
      length--; // decrement for 0-index array;
      if (length > 9) {
        lengths[9]++;
      } else {
        lengths[length]++;
      }
      state = OUT;
      length = 0;
    } else if (state == OUT) {
      state = IN;
      length++;
    } else {
      length++;
    }
  }


  printf("Word length histogram:");
  for (j = 10; j >= 1; j--) {
    for (i = 0; i <= 9; i++) {
      if (lengths[i] >= j) {
        printf(" *");
      } else {
        printf("  ");
      }
    }
    printf("\n");
  }
  printf(" 1 2 3 4 5 6 7 8 9\n");
}
