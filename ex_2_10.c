// Exercise 2.10
// Rewrite the function lower, which converts upper case letters to lower case, with a conditional expression instead of if-else.
#include <stdio.h>

void lower(char s[]);

void lower(char s[])
{
  int c, i;
  i = 0;
  while ((c = s[i]) != '\0')
    s[i++] = (c >= 'A' && c <= 'Z') ? c + ('a' - 'A') : c;
}

int main(void)
{
  char s[14] = "PLOppERS! 97!";
  lower(s);
  printf("%s\n", s);
}
