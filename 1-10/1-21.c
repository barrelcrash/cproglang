/*
 * this solution is not quite in the spirit of the K&R requirements
 * as I understand them - it does not track tab stops independent of
 * a given span of whitespace, but takes whitespace span by span and
 * replaces them with as many tabs as it can with a given (assumed)
 * tab length, and then fills the remainder with spaces
 */
#include <stdio.h>

#define MAX 1000
#define TABSTOP 4

void entab(char s[], int len);
int getLine(char s[], int lim);
int storeLine(char s[], int sLen, char o[], int totalLen);

int main() {

  int len;
  int totalLen = 0;
  char line[MAX];
  char output[MAX * MAX];

  while ((len = getLine(line, MAX)) > 0) {
    entab(line, len);
    totalLen += storeLine(line, len, output, totalLen);
  }

  printf("\n");
  printf("result: \n");
  printf(output);
}

void entab(char s[], int len) {

  int ws = 0; // track spaces

  for (int i = 0; i < len; i++) {
    // count spaces
    if (s[i] == ' ') {
      ws++;
    } else if (s[i] != ' ') {
      if (ws >= TABSTOP) {
        int numTabs = (ws - (ws % TABSTOP)) / TABSTOP;
        i -= ws; 

        // insert tabs
        int nI = i + numTabs;
        for (i; i < nI; i++) {
          s[i] = '\t';
        }

        // add extra spaces if any
        int nW = i + (ws % TABSTOP);
        for (i; i < nW; i++) {
          s[i] = ' ';
        }

        // offset remaining chars
        for (int t = i; t < len; t++) {
          s[t] = s[t + (ws - numTabs - (ws % TABSTOP))];
        }
      }
      
      ws = 0;
    }
  }
}

int storeLine(char s[], int sLen, char o[], int totalLen) {

  int i;

  for (i = 0; s[i] != '\0'; i++, totalLen++) {
    o[totalLen] = s[i]; 
  }

  return i;
}

int getLine(char s[], int lim) {

  int c, i;

  for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
    s[i] = c;
  }

  if (c == '\n') {
    s[i] = c;
    i++;
  }

  s[i] = '\0';

  return i;
}

