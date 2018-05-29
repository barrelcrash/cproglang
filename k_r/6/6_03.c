/*
 * Write a cross-referencer that prints a list of all
 * words in a document and, for each word, a list of
 * the line numbers on which it occurs. Remove noise
 * words like "the", "and", and so on.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define BUFSIZE 100
#define MAXWORD 100
#define MAXLINE 100
#define TRUE 1
#define FALSE 0

struct tnode {
  struct tnode *left;
  struct tnode *right;
  int lineindex;
  int lines[MAXLINE];
  char *word;
};

struct tnode *addtree(struct tnode *, char *, int);
int isnoise(char *w);
int isvalidchar(int);
int getch(void);
int getword(char *, int);
struct tnode *talloc(void);
void treeprint(struct tnode *);
void ungetch(int);

// in a non-demo this list would be much longer
static char* noisetab[] = {
  "and",
  "not",
  "or",
  "the",
  NULL
};

/* similar var grouping */
int main(int argc, char *argv[]) {
  struct tnode *root;
  char word[MAXWORD];
  int c, i;
  int linenum = 1;

  root = NULL;
  while ((c = getword(word, MAXWORD)) != EOF) {
    if (c == '\n') {
      linenum++;
    } else if (isalpha(word[0]) && !isnoise(word)) {
      root = addtree(root, word, linenum);
    }
  }
  treeprint(root);
  return 0;
}

int isnoise(char *w) {
  int i;

  for (i = 0; noisetab[i] != NULL; i++) {
    if (strcmp(noisetab[i], w) == 0) {
      return TRUE;
    }
  }
  return FALSE;
}

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w, int linenum) {
  int cond;
  if (p == NULL) { // a new word has arrived

    // word
    p = talloc();
    p->word = strdup(w);

    // lines and lineindex
    p->lineindex = 0;
    p->lines[0] = linenum;
    p->lineindex++;

    //children
    p->left = p->right = NULL;
  } else if ((cond = strcmp(w, p->word)) == 0) { // present word
    (p->lines)[p->lineindex] = linenum;
    p->lineindex++;
  } else if (cond < 0)
    p->left = addtree(p->left, w, linenum); // new word - left
  else
    p->right = addtree(p->right, w, linenum); // new word - right
  return p;
}

struct tnode *talloc(void) {
  // allocate space for 100 100-char words on top of struct itself
  return (struct tnode *) malloc(
      sizeof(struct tnode)
      + (MAXWORD * sizeof(char))
      + (MAXLINE * (MAXLINE * sizeof(int)))
      );
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p) {
  if (p != NULL) {
    treeprint(p->left);

    int i;

    printf("%s: (%d) ", p->word, p->lineindex);
    for (i = 0; i < p->lineindex; i++) {
      printf("%d", p->lines[i]);
      if (i != p->lineindex - 1) {
        printf(", ");
      }
    }
    printf("\n");

    treeprint(p->right);
  }
}

int getword(char *word, int lim) {
  int c, getch(void);
  void ungetch(int);
  char *w = word;

  while (isspace(c = getch()))
    if (c == '\n')
      return c;
  if (c != EOF)
    *w++ = c; // get first char
  if (!isalpha(c)) { // first char must be alpha
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
