/*
 * regen
 *
 * generate strings using regex-like
 * patterns.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 5000
#define MAX_RULES 100
#define MAXBUF 100
#define MAX_DIGIT 9

#define RULE_INIT {0, NULL, 0}

enum ruletypes {
  INVALID = 0,
  LITERAL,
  DIGIT,
  RANGE
};

typedef struct Rule Rule;
struct Rule {
  int type;
  char *value;
};

/** global variables **/
Rule rules[MAX_RULES];
int ruleslen = 0;

/** function declarations **/
void parseRuleString(Rule*, char**);
char *concatRuleValues(Rule*);

Rule *createLiteral(char[]);
Rule *createDigitRule();
Rule *createRangeRule(char[]);

int randomNumberInclusive(int, int);
char *strdupl(char *);

int main(int argc, char **argv) {

  int opt;

  // option flags
  while (--argc > 0 && *(*++argv) == '-') {
    while ((opt = *++(*argv))) {
      switch (opt) {
        case 'x':
          printf("sample opt1 found\n");
          break;
      }
    }
  }

  // initialize ruleset
  Rule rules[MAX_RULES];

  if (argc != 1)
    printf("usage: \n");

  srand(time(NULL));

  parseRuleString(&rules[0], argv);

  printf("%s\n", concatRuleValues(rules));
}

char *concatRuleValues(Rule *rulep) {
  char *temp = malloc(sizeof(char));
  while (--ruleslen != 0 && rulep->type > 0) {
    temp = realloc(temp, sizeof(temp) + sizeof(rulep->value));
    strcat(temp, rulep->value);
    rulep++;
  }
  return temp;
}

void parseRuleString(Rule *rulep, char **s) {

  do {
    if (**s == '\\') {
      if (*++(*s) == 'd') {
        *rulep = *createDigitRule();
        rulep++;
        ruleslen++;
      }
    } if (**s == '[') {
      char buf[MAXBUF];
      int i;

      i = 0;

      while(*++(*s) != ']') {
        buf[i++] = **s;
      }

      if (strlen(buf) > 0) {
        *rulep = *createRangeRule(buf);
        rulep++;
        ruleslen++;
      }

    } else {
      char buf[] = {**s, '\0'};
      *rulep = *createLiteral(buf);
      rulep++;
      ruleslen++;
    }
  } while (*++(*s) != '\0');
}

Rule *createLiteral(char token[]) {
  Rule *temp = (Rule *) malloc(sizeof(Rule));
  temp->type = LITERAL;
  temp->value = (char *) strdupl(token);
  return temp;
}

Rule *createDigitRule() {
  Rule *temp = (Rule *) malloc(sizeof(Rule));

  char token[] = {randomNumberInclusive(0, MAX_DIGIT) + '0', '\0'};

  temp->type = DIGIT;
  temp->value = (char *) strdupl(token);
  return temp;
}

Rule *createRangeRule(char buf[]) {

  Rule *temp = (Rule *) malloc(sizeof(Rule));

  temp->type = RANGE;

  int possible[MAX]; // possible values
  unsigned int i, j, start, end;

  j = 0;

  for (i = 0; i < strlen(buf) - 1; i++) {
    if (buf[i] == ']') {
      break; // done creating range
    } else if (buf[i] == '-' && i != 0) {
      start = buf[i - 1];
      end = buf[++i];
    } else if (buf[i + 1] == '-') {
      continue; // ignore prior to `-` handle it in the above cond
    } else {
      possible[j++] = buf[i];
      continue; // literal charcter, add to possible and continue
    }

    possible[j++] = randomNumberInclusive(start, end);
  }

  char token[] = {possible[randomNumberInclusive(0, j - 1)], '\0'};

  temp->value = (char *) strdupl(token);

  return temp;
}

int randomNumberInclusive(int l, int u) {

  if (u < l) {
    printf("randomNumberInclusive: lower value greater than upper value");
    return -1;
  }

  int offset = u - l;

  int div = RAND_MAX/(offset + 1);
  int val;

  do {
    rand();
    val = rand() / div;
  } while (val > MAX_DIGIT);

  return val + l;
}

char *strdupl(char *src) {
  size_t len = strlen(src) + 1;
  char *s = malloc(len);
  if (s == NULL)
    return NULL;
  return (char *) memcpy(s, src, len);
}
