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
char *concatRuleValues(struct rule*);

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

  printf("regency result: %s\n", concatRuleValues(rules));
}

char *concatRuleValues(struct rule *rulep) {
  char *temp = malloc(sizeof(char));
  while (rulep->type > 0) {
    realloc(temp, sizeof(temp) + sizeof(rulep->value));
    strcat(temp, rulep->value);
    rulep++;
  }
  return temp;
}

void parseRuleString(struct rule *rulep, char **s) {

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
