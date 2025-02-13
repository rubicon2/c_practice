#include <stdio.h>

#define MAX_LINE    1000
#define MAX_STRINGS 1000

int getline(char copy_to[], int max_length);
int getlength(char str[]);
void copyline(char copy_to[], char copy_from[]);

// Exercise 1.17 - Print all input lines longer than 80 characters.
int main()
{
  char long_lines[MAX_STRINGS][MAX_LINE];
  int lines_saved = 0;

  char current_line[MAX_LINE];

  int current_length = 0;
  int min_length = 80;
  while ((current_length = getline(current_line, MAX_LINE)) > 0) {
    printf("length: %d\n", getlength(current_line));
    if (current_length >= min_length) {
      copyline(long_lines[lines_saved], current_line);
      ++lines_saved;
    }
  }

  for (int i = 0; i < lines_saved; ++i) {
    printf("%s", long_lines[i]);
  }
}

int getline(char copy_to[], int max_length)
{
  int c, length;
  length = 0;
  while (length < max_length - 1 && (c = getchar()) != '\n' && c != EOF) {
    copy_to[length] = c;
    ++length;
  }
  // Length was already incremented from last iteration of while loop.
  if (c == '\n') copy_to[length] = '\n';
  // Don't increment length here - if EOF is reached we want this to return a length of zero.
  copy_to[length + 1] = '\0';
  return length;
}

int getlength(char str[]) {
  int i = 0;
  while (str[i] != '\0')
    ++i;
  return i;
}

void copyline(char copy_to[], char copy_from[])
{
  int i = 0;
  while ((copy_to[i] = copy_from[i]) != '\0')
    ++i;
}
