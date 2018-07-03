/* Add the -d ("directory order") option, which makes comparison
 * only on letters, numbers, and blanks. Make sure it works in
 * conjunction with -f.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000
#define MAXLEN 1000

char *lineptr[MAXLINES];

/* function decs */
void cust_qsort(
    void *lineptr[],
    int left,
    int right,
    int descending,
    int caseFlag,
    int directoryFlag,
    int (*comp)(void*, void*, int, int));
int numcmp(char*, char*, int, int);
int qsort_strcmp(char *, char *, int, int);

void swap(void*[], int, int);
int readlines(char*[], int);
void writelines(char*[], int);
int cust_getline(char[], int);
char lowercase(char);
int isAlphaNumWs(char);

/* 5-14 */
int main(int argc, char *argv[]) {
  int nlines;
  int numeric,
      descending,
      caseFlag,
      directoryFlag = 0;

  if (argc > 1) {
    for (int i = 1; i < argc; i++) {
      if (strcmp(argv[i], "-n") == 0)
        numeric = 1;
      if (strcmp(argv[i], "-r") == 0)
        descending = 1;
      if (strcmp(argv[i], "-f") == 0)
        caseFlag = 1;
      if (strcmp(argv[i], "-d") == 0)
        directoryFlag = 1;
    }
  }

  if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
    cust_qsort(
        (void **) lineptr,
        0,
        nlines - 1,
        descending,
        caseFlag,
        directoryFlag,
        (int (*)(void*,void*,int,int))(numeric ? numcmp : qsort_strcmp));
    printf("\nSorted result:\n");
    writelines(lineptr, nlines);
  } else {
    printf("input too big to sort\n");
    return 1;
  }
}

/* cust_qsort: sort v[left]...v[right] into increasing order */
void cust_qsort(void *v[], int left, int right, int descending, int caseFlag, int directoryFlag,
    int (*comp)(void *, void *, int, int)) {

  if (left >= right)
    return;
  swap(v, left, (left + right)/2);
  int last = left;
  for (int i = left + 1; i <= right; i++)
    if (descending ?
        ((*comp)(v[i], v[left], caseFlag, directoryFlag) > 0)
        : ((*comp)(v[i], v[left], caseFlag, directoryFlag) < 0))
      swap(v, ++last, i);
  swap(v, left, last);
  cust_qsort(v, left, last - 1, descending, caseFlag, directoryFlag, comp);
  cust_qsort(v, last + 1, right, descending, caseFlag, directoryFlag, comp);
}

int numcmp(char *s1, char *s2, int caseFlag, int directoryFlag) {
  double v1, v2;
  v1 = atof(s1);
  v2 = atof(s2);
  if (v1 < v2)
    return -1;
  else if (v1 > v2)
    return 1;
  else
    return 0;
}

/* qsort_strcmp: case-insensitive strcmp */
int qsort_strcmp(char *s1, char *s2, int caseFlag, int directoryFlag) {
  char s1c, s2c;
  for ( ; ; s1++, s2++) {
    // if 'directoryFlag' flag, skip all non-alphanumws
    if (directoryFlag) {
      for ( ; *s1 != '\0' && !isAlphaNumWs(*s1); s1++)
        ;
      for ( ; *s2 != '\0' && !isAlphaNumWs(*s2); s2++)
        ;
    }
    // if caseInsensitive flag, convert all uppers to lowers
    s1c = caseFlag ? lowercase(*s1) : *s1;
    s2c = caseFlag ? lowercase(*s2) : *s2;

    if (s1c != s2c)
      break;
    if (*s1 == '\0')
      return 0;
  }
  return s1c - s2c;
}

/* lowercase: convert char to lowercase */
char lowercase(char c) {
  int ascii_offset = 'a' - 'A';
  if (c >= 'A' && c <= 'Z')
    return c + ascii_offset;
  return c;
}

int isAlphaNumWs(char c) {
  if ((c >= 'A' && c <= 'Z')
      || (c >= 'a' && c <= 'z')
      || (c >= '0' && c <= '9')
      || (c == ' ')
      || (c == '\t'))
    return 1;

  return 0;
}

void swap(void *v[], int i, int j) {
  void *temp;
  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines) {
  int len, nlines;
  char *p, line[MAXLEN];

  nlines = 0;
  while((len = cust_getline(line, MAXLEN)) > 0)
    if (nlines >= maxlines || (p = malloc(len)) == NULL)
      return -1;
    else {
      line[len - 1] = '\0'; // delete newline
      strcpy(p, line);
      lineptr[nlines++] = p;
    }
  return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines) {
  int i;
  for (i = 0; i < nlines; i++)
    printf("%s\n", lineptr[i]);
}

int cust_getline(char s[], int lim) {
  int c, i;
  
  for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
    s[i] = c;
  if (c == '\n') {
    s[i] = c;
    ++i;
  }
  s[i] = '\0';
  return i;
}
