/*
 * Exercise 3-3
 * Write a function expand(s1,s2) that expands shorthand notations
 * like a-z in the string s1 into the equivalent complete list 
 * abc...xyz in s2. Allow for letters of either case and digits,
 * and be prepared to handle cases like a-b-c and a-z0-9 and -a-z.
 * Arrange that a leading or trailing - is taken literally.
 */

#include <stdio.h>
#include <string.h>

#define MAX 1000
#define TRUE 1
#define FALSE 0

void printexpand(char s[]);
void expand(char s1[], char s2[]);
int isalphanumeric(char c);

int main()
{
  printexpand("a-c\n");
  printexpand("0-9\n");
  printexpand("E-Y\n");
  printexpand("-a-t\n");
  printexpand("a-t-\n");
  printexpand("a-t4-7\n");
  printexpand("a-c-e\n");
  printexpand("0-a\n");
}

void printexpand(char s[]) {
  char target[MAX];
  expand(s, target);
  printf(target);
}

void expand(char s1[], char s2[])
{
  // clean up target
  for (int i = 0; i < sizeof(s2); i++)
    s2[i] = 0;
  // 48-57, 65-90, 97-122

  int expanding = FALSE; // track prior expansions and avoid repeat chars
  
  for (int i = 0, j = 0; i < strlen(s1); i++) {
    if (s1[i] == '-') { // potential middle of a expansion expression, process
      if (isalphanumeric(s1[i - 1]) && isalphanumeric(s1[i + 1])) {
        for (int k = s1[i - 1]; k <= s1[i + 1]; k++) {
          if (expanding) // don't repeat already-expanded hars
            k++;
          if (isalphanumeric(k)) // don't add non-alphanumerics
            s2[j++] = k;
        }
        expanding = TRUE;
        i++; // skip past the expansion terminus
      } else {
        expanding = FALSE;
        s2[j++] = s1[i]; 
      }
    } else if (!(s1[i + 1] == '-' && isalphanumeric(s1[i + 2]))) { // not start of expansion expr, treat literally
      expanding = FALSE;
      s2[j++] = s1[i]; 
    }
  }
}

/*
 *
 */
int isalphanumeric(char c) {
  if ((c >= '0' && c <= '9')
      || (c >='A' && c <= 'Z')
      || (c >='a' && c <= 'z')) {
    return 1;
  }
  return 0;
}
