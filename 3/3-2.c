#include <stdio.h>

#define MAX 1000

void escape(char s[] , char t[]);
void unescape(char s[] , char t[]);
int getInput(char s[]);

int main() {
  char from[MAX], to[MAX];

  getInput(from);
  escape(from, to);

  printf("\n");
  printf("escaped result: \n");
  printf(to);

  unescape(to, from);

  printf("\n");
  printf("unescaped result: \n");
  printf(from);

  return 0;
}

void escape(char s[], char t[]) {
  int i, j, c;

  i = 0;
  j = 0;

  while ((c = s[i]) != '\0') {
    switch (c) {
      case '\n':
        t[j++] = '\\';
        t[j++] = 'n';
        break;
      case '\t':
        t[j++] = '\\';
        t[j++] = 't';
        break;
      default:
        t[j++] = c;
        break;
    }

    i++;
  }

}

void unescape(char s[], char t[]) {
  int i, j, c;

  i = 0;
  j = 0;

  while ((c = s[i]) != '\0') {
    if (c == '\\') {
      c = s[++i];
      switch (c) {
        case 'n':
          t[j++] = '\n';
          break;
        case 't':
          t[j++] = '\t';
          break;
      }
    } else {
      t[j++] = c;
    }

    i++;
  }

} 

int getInput(char s[]) {
  int c, i;

  for (i = 0; (c = getchar()) != EOF ; ++i) {
    s[i] = c;
  }

  if (c == '\n') {
    s[i] = c;
    i++;
  }

  s[i] = '\0';

  return i;
}

