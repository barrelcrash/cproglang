#include <stdio.h>

#define MAXLINE 1000

int customGetLine(char s[], int lim);
void reverseString(char s[]);
int lineLength(char s[]);

int main() {
    int len;
    char line[MAXLINE];

    while((len = customGetLine(line, MAXLINE)) > 0 ) {
      reverseString(line);
      printf("%s", line);
    }

    return 0;
}

int customGetLine(char s[], int lim) {
    int c, i;
    for(i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;
    if(c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

void reverseString(char s[]) {
  int i, j;
  int k = 0;
  int len = lineLength(s);
  char r[len];

  for (i = len - 3; i >= 0; i--) {
    r[i] = s[k++];
  }

  r[len - 2] = '\n';
  r[len - 1] = '\0';

  for (j = 0; j < len; j++) {
    s[j] = r[j];
  }
}

int lineLength(char s[]) {
  int i;

  for (i = 0; s[i] != '\0'; i++) {}

  return ++i;
}
