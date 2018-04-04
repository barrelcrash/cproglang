/*
 * regen
 *
 * generate strings using regex-like
 * patterns.
 */

#include <stdio.h>

#define MAX 5000
#define MAX_RULES 100

#define RULE_INIT {NULL, 0, NULL, 0}

struct rule {
  char *key;
  int keylen;
  char *value;
  int valuelen;
};

/** global variables **/
struct rule rules[MAX_RULES];
int ruleslen = 0;

/** function declarations **/
void parseRuleString(char**);

int main(int argc, char **argv) {

  int opt;

  // option flags
  while (--argc > 0 && *(*++argv) == '-') {
    while ((opt = *++(*argv))) {
      switch (opt) {
        case 'x':
          printf("sample opt1 found\n");
          break;
        case 'y':
          printf("sample opt2 found\n");
          break;
      }
    }
  }

  parseRuleString(argv); 
}

// TODO: create dynamic rule building

void parseRuleString(char **s) {
  printf("rule string: %s\n", *s);
  int rulelen = sizeof(*s) / sizeof(**s);

  // TODO: implement literal rule parsing
  while (--rulelen > 0) {
  }
}

