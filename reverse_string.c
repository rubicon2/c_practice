#include <stdio.h>

#define MAX_LENGTH 1000
#define       TRUE    1
#define      FALSE    0

int get_line(char str[], int max_length, int include_newline);

// Exercise 1.19 - write a function reverse(str) that reverses a char string, a line at a time.
int main()
{
  int c, length;
  char line[MAX_LENGTH];

  do {
    length = get_line(line, MAX_LENGTH, TRUE);
    if (length > 0) {
      for (int i = length - 1; i >= 0; --i) {
        printf("%c", line[i]);
      }
      printf("\n");
    }
  } while (length != EOF);
}

int get_line(char str[], int max_length, int include_newline)
{
  int c, i;
  i = 0;
  while (i < MAX_LENGTH - 1 && (c = getchar()) != '\n') {
    if (c == EOF) return EOF;
    str[i] = c;
    ++i;
  }
  if (include_newline == TRUE)
    if (c == '\n') str[i] = '\n';
  str[i + 1] = '\0';
  return i;
}
