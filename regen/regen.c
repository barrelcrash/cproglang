/*
 * regen
 *
 * generate strings using regex-like
 * patterns.
 */

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define MAX 5000
#define MAX_RULES 100

#define RULE_INIT {0, NULL, 0}

enum ruletypes {
  INVALID = 0,
  LITERAL
};

struct rule {
  int type;
  char *value;
  int valuelen;
};

/** global variables **/
struct rule rules[MAX_RULES];
int ruleslen = 0;

/** function declarations **/
void parseRuleString(struct rule*, char**);
struct rule *createRule(char[]);

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

  // initialize ruleset
  struct rule rules[MAX_RULES];
  parseRuleString(&rules[0], argv); 

  // TODO: build string from literal rules
  for (int i = 0; rules[i].type > 0; i++) {
    printf("rule type: %d\n", rules[i].type);
    printf("rule string: %s\n", rules[i].value);
  }
}

void parseRuleString(struct rule *rulep, char **s) {
  printf("rule string: %s\n", *s);

  int slen = strlen(*s);

  // TODO: implement digit rule parsing
  while (--slen >= 0) {
    char buf[] = {*(*s)++, '\0'};
    *rulep = *createRule(buf);
    rulep++;
  }
}

struct rule *createRule(char token[]) {
  struct rule *temp = malloc(sizeof(struct rule));
  temp->type = LITERAL;
  temp->value = strdup(token);
  temp->valuelen = strlen(token);
  return temp;
}
