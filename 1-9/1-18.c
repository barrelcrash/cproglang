#include <stdio.h>

#define MAXLINE 1000
#define ALLLINES 1000000
#define IN 1
#define OUT 0

int getline(char line[], int maxline);
void trimline(char line[]);

main() {
  int len, i, j, a;
  char line[MAXLINE];
  char all[ALLLINES];

  a = 0;

  printf("please provide text:\n");

  while ((len = getline(line, MAXLINE)) > 0) {
    trimline(line); 

    for (i = 0; i < len; i++) {
      all[a] = line[i];
      a++;
    }
  }

  for (j = 0; j <= a; j++) {
    putchar(all[j]);
  }

  return 0;
}

int getline(char line[], int maxline) {

  int c, i;

  for (i = 0; i < maxline - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
    line[i] = c;
  }

  if (c == '\n') {
    line[i] = c;
    i++;
  }

  return i;
}

void trimline(char line[]) {
  int i, c, state, last;

  state = OUT;
  
  // find start of last whitespace substring
  for (i = 0; i < MAXLINE; i++) {
    c = line[i];

    if (c == ' ' || c == '\t' || c == '\n') {
      if (state = IN) {
        last = i;
      }
      state = OUT;
    } else if (state == OUT) {
      state = IN;
    }
  }
  
  // make every character after 'last' null
  for (i = 0; i < MAXLINE; i++ ) {
    if (i >= last) {
      line[i] = '\0';
    }
  }

  // make sure line has newline at end
  line[last] = '\n';
}
