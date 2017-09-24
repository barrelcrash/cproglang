#include <stdio.h>

main() {
  printf("How would you test the word count program?\n");
  printf("What kind of input are most likely to uncover\n");
  printf("bugs if there are any?\n");
  
  printf("\n");
  
  printf("Pass the program the the following set of lines, e.g.:\n");
  printf("1. A 'standard line' like an English sentence.\n");
  printf("2. A similar line, but demarcated with tabs.\n");
  printf("3. A line with no whitespace.\n");
  printf("4. A line consisting of nothing but whitespace.\n");
  printf("5. A line with a mixture of tabs, spaces, and words.\n");
  printf("\n");
  printf("Lines 3 and 4 would most likely return bugs, as they\n");
  printf("Do not move in and out of the word state as the program\n");
  printf("expects, and would likely return unanticipated counts\n");
  printf("or potentially even fail, not having generated a count value.\n");
}



