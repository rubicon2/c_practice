// Exercise 3.2
// Write a function escape(s, t) that converts chatacters like newline and tab into visible escape sequences
// like \n and \t, as it copies the string t to s. Use a switch. Write a function for the other direction as
// well, converting escape sequences into the real characters.

#include <stdio.h>

#define MAX_LINE 1000
#define     TRUE    1
#define    FALSE    0

void escape(char s[], char t[]);
void unescape(char s[], char t[]);
int get_line(char s[], int max_line);

void escape(char s[], char t[])
{
  int i, j;
  i = j = 0;
  // This will skip copying over \0! As when that happens, the loop is not entered again.
  while ((s[i] = t[j]) != '\0') {
    switch (s[i]) {
      case '\t': {
        // Overwrite \t with a literal backslash and a t.
        s[i] = '\\';
        s[++i] = 't';
        break;
      }

      case '\n': {
        s[i] = '\\';
        s[++i] = 'n';
        break;
      }

      case '\\': {
        s[i] = '\\';
        s[++i] = '\\';
        break;
      }

      case '\'': {
        s[i] = '\\';
        s[++i] = '\'';
        break;
      }

      case '\"': {
        s[i] = '\\';
        s[++i] = '\"';
        break;
      }
    }
    ++i;
    ++j;
  }
  s[i] = '\\';
  s[++i] = '0';
  // Don't forget the real string terminator.
  s[++i] = '\0';
}

void unescape(char s[], char t[])
{
  int i, j, in_escaped_char;

  i = j = 0;
  in_escaped_char = FALSE;
  while ((s[i] = t[j]) != '\0') {
    if (in_escaped_char) {
      // We want to overwrite the backslash already put in the array.
      // Looks weird decrementing it and then doing s[i + 1] in the switch,
      // but this is preferable to doing --i or i - 1 in every switch case.
      --i;
      switch (s[i + 1]) {
        case '\\':
          s[i] = '\\';
          break;
        
        case 't':
          s[i] = '\t';
          break;
        
        case 'n':
          s[i] = '\n';
          break;

        case '0':
          s[i] = '\0';
          break;

        case '\'':
          s[i] = '\'';
          break;

        case '\"':
          s[i] = '\"';
          break;
      }
      in_escaped_char = FALSE;
    } else {
      if (s[i] == '\\') {
        in_escaped_char = TRUE;
      }
    }
    ++i;
    ++j;
  }
  s[i] = '\0';
}

int get_line(char s[], int max_line)
{
  int i = 0;
  while (i < max_line - 1 && (s[i] = getchar()) != '\n') 
    ++i;
  s[i] = '\n';
  s[i + 1] = '\0';
  return i;
}

int main(void)
{
  char s[MAX_LINE], t[MAX_LINE];
  get_line(t, MAX_LINE);
  escape(s, t);
  printf("%s\n", s);

  get_line(t, MAX_LINE);
  unescape(s, t);
  printf("%s\n", s);
}
