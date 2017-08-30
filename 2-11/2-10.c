#include <stdio.h>

int lower(int c);
void applyLower(char s[]);

int main() {

  char l[] = "my lower string\n";
  char camel[] = "My Camel String\n";
  char u[] = "MY UPPER STRING\n";

  applyLower(l); 
  applyLower(camel); 
  applyLower(u); 

  printf(l);
  printf(camel);
  printf(u);

}

void applyLower(char s[]) {
  for (int i = 0; s[i] != '\0'; i++) {
    s[i] = lower(s[i]);
  }
}

int lower(int c) {
  return (c >= 'A' && c <= 'Z') ? (c + 'a' - 'A') : c;
}
