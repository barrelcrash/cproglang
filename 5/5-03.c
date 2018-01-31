/* Write a pointer version of the function strcat
 * that we showed in Chapter 2: strcat(s,t) copies
 * the string t to the end of s.
 */

#include <stdio.h>

void astrcat(char[], char[]);
void pstrcat(char*, char*);

int main()
{

  char string1[] = "all";
  char string2[] = "your";
  char string3[] = "base";
  char string4[] = "are";

  astrcat(string1, string2);
  printf(string1);
  
  printf("\n");

  pstrcat(string3, string4);
  printf(string3);
}

// strcat - array version
void astrcat(char s[], char t[])
{
  int i, j;

  i = j = 0;
  while (s[i] != '\0') // find end of s
    i++;
  while ((s[i++] = t[j++]) != '\0') // copy t
    ;
}

// strcat - pointer version
void pstrcat(char *s, char *t)
{
  while (*s) // find end of s
    *s++; 

  while (*s++ = *t++) // copy t
    ;
}
