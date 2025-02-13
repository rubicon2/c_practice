#include <stdio.h>

#define MAXLINE 10

int getline(char copy_to[], int max_length);
void copyline(char copy_to[], char copy_from[]);

int main()
{
  char current_line[MAXLINE];
  char longest_line[MAXLINE];
  int current_line_length = 0;
  int longest_line_length = 0;

  while ((current_line_length = getline(current_line, MAXLINE)) > 0) {
    if (current_line_length > longest_line_length) {
      longest_line_length = current_line_length;
      copyline(longest_line, current_line);
    }
  }

  printf("Longest line (%d characters):\n", longest_line_length);
  printf("%s", longest_line);
}

int getline(char copy_to[], int max_length)
{
  int c, length;
  length = 0;
  while ((c = getchar()) != '\n' && c != EOF) {
    // Only copy over the character if copy_to is big enough to hold it.
    if (length < max_length - 1) copy_to[length] = c;
    // But always record the total length even if we cannot store the whole string.
    ++length;
  }
  // If end of line was a newline char, add onto the end as the loop will have been terminated by it.
  if (c == '\n') {
    copy_to[length] = '\n';
    ++length;
  }
  // Add string termination character.
  copy_to[length] = '\0';
  return length;
}

void copyline(char copy_to[], char copy_from[])
{
  int i = 0;
  while ((copy_to[i] = copy_from[i]) != '\0')
    ++i;
}
