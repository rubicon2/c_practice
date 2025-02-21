#include <stdio.h>

#define LIMIT 1000

void print_line(const char s[])
{
  int c, i;
  i = 0;
  while ((c = s[i]) != '\0') {
    printf("%c", s[i]);
    ++i;
  }
  printf("\n");
}

int main(void)
{
  char line[1000];
  int c, i;
  for (i = 0; i < LIMIT - 1 && (c = getchar()) != '\n' && c != EOF; ++i) {
    line[i] = c;
  }
  line[i] = '\0';

  printf("Result:\n");
  print_line(line);

  // Write a loop equivalent to above without using && or ||.
  // If there is some fancy way to do it all in the loop condition, I have no idea what it is.
  for (i = 0; i < LIMIT - 1; ++i) {
    c = getchar();
    if (c == '\n') break;
    if (c == EOF) break;
    line[i] = c;
  }
  line[i] = '\0';

  print_line(line);

  // Ok - each bool expression evaluates to either 1 (true) or 0 (false).
  // We can add the result of all the expressions together and compare.
  // So if all 3 expressions evaluate to true and yield 1 each, this will give a total of 3.
  // If any one of them evaluates to false, we will get 2, and so on.
  // This is obviously way clunkier than the loop using break statements.
  for (i = 0; (i < LIMIT - 1) + ((c = getchar()) != '\n') + (c != EOF) == 3; ++i) {
    line[i] = c;
  }
  line[i] = '\0';

  print_line(line);
}
