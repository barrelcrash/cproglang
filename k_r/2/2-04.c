#include <stdio.h>

#define FALSE 0;
#define TRUE 1;

void squeezeByChar(char s[], int c);
void squeezeByString(char s[], char squeeze[]);
int getStringLength(char s[]);

int main() {
  printf("Squeezing strings\n");

  char string[] = "Thus";
  char c = 'T';

  squeezeByChar(string, c);
  printf(string);
  printf("\n");

  char string2[] = "Thus";
  char d[] = "Tu";

  squeezeByString(string2, d);
  printf(string2);
  printf("\n");

  return 0;
}

// remove instances of char from string
void squeezeByChar(char s[], int c) {
  int i, j;

  for (i = j = 0; s[i] != '\0'; i++) {
    if (s[i] != c) {
      s[j++] = s[i];
    }
  }

  s[j] = '\0';
}

// remove any char[] from string
void squeezeByString(char s[], char squeeze[]) {
  int i, j, k, shouldRemove;
  int squeezeLength = getStringLength(squeeze);

  for (i = j = 0; s[i] != '\0'; i++) {
    // loop thru squeeze, check for presence of s[i]
    shouldRemove = FALSE;
    for (k = 0; k <= squeezeLength; k++) {
      if (s[i] == squeeze[k]) {
        shouldRemove = TRUE;
      }
    }

    // if s[i] not in squeeze, assign it
    if (!shouldRemove) {
      s[j++] = s[i];
    }
  }

  s[j] = '\0';
}

int getStringLength(char s[]) {
  int i;
  char c;

  for (i = 0; (c = s[i]) != '\0'; i++) {}

  i++;

  return i;
}
