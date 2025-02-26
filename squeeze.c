// Exercise 2.4
// Write a function squeeze(s1, s2) that deletes each character in s1 that matches any character in string s2.
#include <stdio.h>
#include <stdlib.h>

#define MAX_STR_LENGTH 100
#define           TRUE   1
#define          FALSE   0

int str_len(const char s[]);
int get_line(char to[]);
void shift_chars(char s[], const int shift_from, const int shift_by);
void squeeze(char s1[], const char s2[]);

int str_len(const char s[])
{
  int i = 0;
  while (s[i] != '\0')
    ++i;
  return i;
}

int get_line(char to[])
{
  int c, i, max_length;
  i = 0;
  // Sub 2 from MAX STR LENGTH as i starts at zero, and to leave room for the \0 we will append at the end of the string/after the loop.
  while ((c = getchar()) != '\n' && i < MAX_STR_LENGTH - 2) {
    if (c == EOF) {
      // Return EOF so calling function knows when to break out of loop, etc.
      return EOF;
    }
    to[i] = c;
    ++i;
  }
  to[i] = '\0';
  // Return length of line, excluding \0.
  return i;
}

void shift_chars(char s[], const int shift_from, const int shift_by)
{
  // Plus one to include the \0 end of string character.
  int length = str_len(s) + 1;
  for (int i = shift_from; i < length && i + shift_by < length; ++i) {
    if (i + shift_by < 0) {
      fprintf(stderr, "Error: shift_chars() tried to shift character into array index %d\n", i + shift_by);
      exit(1);
    }
    s[i + shift_by] = s[i];
    // If last char moved was end of string, skip the rest.
    if (s[i + shift_by] == '\0')
      break;
  }
}

void squeeze(char s1[], const char s2[])
{
  int s1_length = str_len(s1);
  int s2_length = str_len(s2);
  for (int s1_i = 0; s1_i < s1_length; ++s1_i) {
    for (int s2_i = 0; s2_i < s2_length; ++s2_i) {
      if (s1[s1_i] == s2[s2_i]) {
        // Move all chars down by one index, overwriting the char in s1[s1_i].
        shift_chars(s1, s1_i + 1, -1);
        // Move onto next char in s1 - but as length of string has reduced by one, need to decrement s1_i here!
        // Otherwise we will skip a char every time the string chars are shifted.
        --s1_i;
        break;
      }
    }
  }
}

int main(void)
{
  char line_to_filter[MAX_STR_LENGTH];
  char chars_to_remove[MAX_STR_LENGTH];

  printf("Type a string to filter:\n");
  get_line(line_to_filter);

  printf("Type the characters to filter out:\n");
  get_line(chars_to_remove);

  squeeze(line_to_filter, chars_to_remove);
  printf("Filtered:\n");
  printf("%s\n", line_to_filter);
}
