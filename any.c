// Exercise 2.5
// Write the function any(s1, s2) which returns the first location in the string s1 where any char from s2 occurs, or -1 if none appear.
#include <stdio.h>

#define MAX_LINE 1000
#define     TRUE    1
#define    FALSE    0

int get_line(char to[], int max_length);
int str_len(const char s[]);
int any(const char s1[], const char s2[]);

int get_line(char to[], int max_length)
{
  int c, i;
  i = 0;
  while ((c = getchar()) != '\n' && i < max_length - 1) {
    to[i] = c;
    ++i;
  }
  to[i] = '\0';
  return i;
}

int str_len(const char s[])
{
  int i = 0;
  while (s[i] != '\0')
    ++i;
  return i;
}

int any(const char s1[], const char s2[])
{
  int s1_len = str_len(s1);
  int s2_len = str_len(s2);
  for (int s1_i = 0; s1_i < s1_len; ++s1_i) {
    for (int s2_i = 0; s2_i < s2_len; ++s2_i) {
      if (s1[s1_i] == s2[s2_i])
        return s1_i;
    }
  }
  // No chars from s2 found in s1.
  return -1;
}

int main(void)
{
  char s1[MAX_LINE];
  char s2[MAX_LINE];

  printf("Enter a string to search for characters:\n");
  get_line(s1, MAX_LINE);

  printf("Enter characters to look for:\n");
  get_line(s2, MAX_LINE);

  int first_char_index = any(s1, s2);
  if (first_char_index >= 0)
    printf("First char matching search occurs at index %d\n", first_char_index);
  else
    printf("No matching char found\n");
}
