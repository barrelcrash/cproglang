// solution to: https://www.reddit.com/r/dailyprogrammer/comments/6v29zk/170821_challenge_328_easy_latin_squares/dlxqqeo/

#include <stdio.h>

enum boolean {FALSE, TRUE};

int detectLatin(int side, int sq[]);
void reduceAndPrint(int side, int sq[]);
void swapRow(int side, int r[], int o[]);

int main() {

  int side1 = 5;
  int square1[25] = {1, 2, 3, 4, 5, 5, 1, 2, 3, 4, 4, 5, 1, 2, 3, 3, 4, 5, 1, 2, 2, 3, 4, 5, 1};
  printf("square1 is latin?: %d\n", detectLatin(side1, square1));

  if (detectLatin(side1, square1)) {
    reduceAndPrint(side1, square1);
  } else {
    printf("Not a latin square and not reduceable!\n");    
  }

  printf("\n");

  int side2 = 4;
  int square2[16] = {1, 2, 3, 4, 1, 3, 2, 4, 2, 3, 4, 1, 4, 3, 2, 1};

  printf("square2 is latin?: %d\n", detectLatin(side2, square2));
  if (detectLatin(side2, square2)) {
    reduceAndPrint(side2, square2);
  } else {
    printf("Not a latin square and not reduceable!\n");    
  }

  printf("\n");

  int side3 = 5;
  int square3[25] = {1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5};

  printf("square3 is latin?: %d\n", detectLatin(side3, square3));
  if (detectLatin(side3, square3)) {
    reduceAndPrint(side3, square3);
  } else {
    printf("Not a latin square and not reduceable!\n");    
  }

  return 0;
}

int detectLatin(int side, int sq[]) {
  int isLatin = TRUE;

  for (int i = 0; i < (side * side); i++) {
    // check column
    for (int j = side; j <= (side * side); j += side) {
      if (i >= side && i - j >= 0) {
        if (sq[i] == sq[i - j]) {
          isLatin = FALSE;
        }
      }
    }

    // check row
    int rowMod = i % 5;
    int rowStart = i - rowMod;
    for (int k = rowStart; k < (rowStart + 5); k++) {
      if (i != k && sq[i] == sq[k]) {
        isLatin = FALSE;
      }
    }
  }

  return isLatin;
}

void reduceAndPrint(int side, int sq[]) {
  int array[side][side];
  int array2[side][side];
  int j;

  // create 2d array
  for (int i = 0; i < side; i++) {
    for (int j = 0; j < side; j++) {
      int index = (i * side) + j;
      array[i][j] = sq[index];
    }
  }
  
  //  bubble sort
  int swapped;
  do {
    swapped = FALSE;
    for (int i = 1; i < side; i++) {
      if (array[i - 1][0] > array[i][0]) {
        swapRow(side, array[i - 1], array[i]);
        swapped = TRUE;
      }
    }
  } while (swapped == TRUE);

  // print
  for (int i = 0; i < side; i++) {
    for (int j = 0; j < side; j++) {
      printf("%d ", array[i][j]);
    }
    printf("\n");
  }
}

void swapRow(int side, int r[], int o[]) {
  int temp;   

  for (int i = 0; i < side; i++) {
    temp = r[i];
    r[i] = o[i];
    o[i] = temp;
  }
}

