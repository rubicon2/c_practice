#include <stdio.h>

#define  MAX_LINES 1000
#define MAX_LENGTH 1000
#define       TRUE 1
#define      FALSE 0

int get_line(char line[], int max_length);
void copy_line(char to[], char from[]);
void trim_line(char trimmed[], char line[]);
int get_length(char str[]);

// Exercise 1.18 - write a propgram to remove trailing blanks and tabs, and to delete entirely blank lines from input.
int main()
{
  char line[MAX_LENGTH];
  char saved_lines[MAX_LINES][MAX_LENGTH];
  int saved_lines_count = 0;

  while (get_line(line, MAX_LENGTH) != EOF) {
    char trimmed[MAX_LENGTH];
    trim_line(trimmed, line);
    if (get_length(trimmed) > 0) {
      copy_line(saved_lines[saved_lines_count], trimmed);
      ++saved_lines_count;
    }
  }

  printf("Trimmed lines:\n");

  for (int i = 0; i < saved_lines_count; ++i) {
    printf("%s", saved_lines[i]);
  }
}

// Return length unless last char is EOF, in which case return EOF.
int get_line(char line[], int max_length)
{
  int c, i;
  i = 0;
  while ((c = getchar()) != '\n') {
    // If EOF is encountered, return it and abandon getting a line.
    if (c == EOF) return EOF;
    line[i] = c;
    ++i;
  }
  if (c == '\n') line[i] = '\n';
  // Don't include the termination character in the line length.
  line[i + 1] = '\0';
  return i;
}

void copy_line(char to[], char from[])
{
  int i = 0;
  while ((to[i] = from[i]) != '\0')
    ++i;
}

void trim_line(char trimmed[], char line[])
{
  // Remove the whitespace before the first non-whitespace character,
  // and the whitespace after the last non-whitespace character.
  int c, i, first_char_i, last_char_i;
  // Needs to be an impossible array index. -1 seemed like a natural choice.
  first_char_i = last_char_i = -1;
  i = 0;
  // Find the first and last non-whitespace chars of the original string.
  while ((c = line[i]) != '\0') {
    if (c != ' ' && c != '\t') {
      if (first_char_i == -1)
        first_char_i = i;
      last_char_i = i;
    }
    ++i;
  }

  // Map them to the correct indexes of the trimmed char array.
  for (i = 0; i <= last_char_i - first_char_i; ++i) {
    trimmed[i] = line[first_char_i + i];
  }
  

  trimmed[i + 1] = '\0';
}

int get_length(char str[])
{
  int i, c;
  i = 0;
  while (str[i] != '\0' && str[i] != '\n')
    ++i;
  return i;
}
