#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define BUFSIZE 100
#define MAXWORD 100

struct tnode {
  struct tnode *left;
  struct tnode *right;
  int count;
  char *word[];
};

int getword(char *, int);
void ungetch(int);
struct tnode *addtree(struct tnode *, char *, int);
struct tnode *talloc(void);
void treeprint(struct tnode *);
int isvalidchar(int);

/* similar var grouping */
int main(int argc, char *argv[]) {
  struct tnode *root;
  char word[MAXWORD];
  int ccount;

  if (argc > 1)
    ccount = (*++argv)[0] - '0';
  else
    ccount = 6;

  root = NULL;
  while (getword(word, MAXWORD) != EOF)
    if (isalpha(word[0]))
      root = addtree(root, word, ccount);
  treeprint(root);
  return 0;
}

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w, int ccount) {
  int cond;
  if (p == NULL) { // a new word has arrived
    p = talloc();
    p->word[0] = strdup(w);
    p->count++;
    p->left = p->right = NULL;
    // compare - same up to six, but not the same word
  } else if ((cond = strncmp(w, p->word[0], ccount)) == 0) {
    int i;
    int present = 0;
    for (i = 0; i < p->count; i++) {
      if (strcmp(w, p->word[i]) == 0) {
        present = 1;
      }
    }
    if (!present) {
      p->word[p->count] = strdup(w);
      p->count++;
    }
  } else if (cond < 0)
    p->left = addtree(p->left, w, ccount);
  else
    p->right = addtree(p->right, w, ccount);
  return p;
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p) {
  if (p != NULL) {
    treeprint(p->left);

    int i;

    for (i = 0; i < p->count; i++) {
      printf("%s\n", p->word[i]);
    }
    printf("\n");

    treeprint(p->right); }
}

struct tnode *talloc(void) {
  // allocate space for 100 100-char words on top of struct itself
  return (struct tnode *) malloc(sizeof(struct tnode) + (MAXWORD * (MAXWORD * sizeof(char))));
}

int getword(char *word, int lim) {
  int c, getch(void);
  void ungetch(int);
  char *w = word;

  while (isspace(c = getch()))
    ;
  if (c != EOF)
    *w++ = c;
  if (!isalpha(c)) {
    *w = '\0';
    return c;
  }
  for ( ; --lim > 0; w++)
    if (!isvalidchar(*w = getch())) {
      ungetch(*w);
      break;
    }
  *w = '\0';
  return word[0];
}

int isvalidchar(int c) {
  return isalnum(c) || c =='_';
}

/*
 * CHAR BUFFER
 */
char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

int getch(void) /* get a (possibly pushed back) character */
{
  return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
  if(bufp >= BUFSIZE)
    printf("ungetch: too many characters\n");
  else
    buf[bufp++] = c;
}
