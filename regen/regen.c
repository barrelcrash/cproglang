/*
 * regen
 *
 * generate strings using regex-like
 * patterns.
 */

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>

#define MAX 5000
#define MAX_RULES 100
#define MAX_DIGIT 9

#define RULE_INIT {0, NULL, 0}

enum ruletypes {
  INVALID = 0,
  LITERAL,
  DIGIT
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
char *concatRuleValues(struct rule*);

struct rule *createLiteral(char[]);
struct rule *createDigitRule();

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
  do {
    if (**s == '\\') {
      if (*++(*s) == 'd') {
        *rulep = *createDigitRule();
        rulep++;
      }
    } else {
      char buf[] = {**s, '\0'};
      *rulep = *createLiteral(buf);
      rulep++;
    }
  } while (*(*s)++ != '\0');
}

struct rule *createLiteral(char token[]) {
  struct rule *temp = (struct rule *) malloc(sizeof(struct rule));
  temp->type = LITERAL;
  temp->value = strdup(token);
  temp->valuelen = strlen(token);
  return temp;
}

struct rule *createDigitRule() {
  struct rule *temp = (struct rule *) malloc(sizeof(struct rule));

  int div = RAND_MAX/(MAX_DIGIT + 1);
  int val;

  srand(time(NULL));
  do {
    rand();
    val = rand() / div;
  } while (val > MAX_DIGIT);

  char token[] = {val + '0', '\0'};

  printf("%d\n", val);

  temp->type = DIGIT;
  temp->value = strdup(token);
  temp->valuelen = strlen(token);
  return temp;
}
