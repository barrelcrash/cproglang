#include <stdio.h>

#define MAXLINE 1000

char line[MAXLINE];

int getline(void);

main() {
   
  int len;

  extern char line[];

  while ((len = getline()) > 0) {
    printf("%d: ", len);
    for (int i = 0; i < len; i++) {
      putchar(line[i]);
    }
  }
}

int getline(void) {
  int c, i;
  extern char line[];

  for (i = 0; ((i < MAXLINE - 1) + ((c=getchar()) != EOF) + (c != '\n')) == 3; i++) {
    line[i] = c;
  }

  if (c == '\n') {
    line[i] = c;
    i++;
  }

  line[i] = '\0';
  return i;
}
