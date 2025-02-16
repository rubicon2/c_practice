#include <stdio.h>

#define    MAX_LENGTH 1000
#define          TRUE    1
#define         FALSE    0
#define MAX_LINE_COLS   50
#define TAB_COL_WIDTH    4

// Function prototypes.
void print_col_guide(int max_cols);
int get_length(char str[], int include_return);
void get_substr(char to[], char from[], int start_i, int end_i);
int get_line(char str[], int max_length, int include_return);

// Exercise 1.22 - fold long input lines into two or more shoprter lines. I.e. line breaks! What prettier does.
// Doesn't really deal with tabs well, but otherwise seems ok.
int main()
{
  char line[MAX_LENGTH], word[MAX_LENGTH];
  int length, in_word, word_start_i, word_length;

  do {
    length = get_line(line, MAX_LENGTH, TRUE);
    word_start_i = 0;
    in_word = FALSE;

    // print_col_guide(MAX_LINE_COLS);

    for (int i = 0, col = 0; i < length; ++i) {
      char c = line[i];
      if (c == ' ' || c == '\t' || c == '\n') { 
        if (in_word == TRUE) {
          if (c == '\t') col += TAB_COL_WIDTH;
          word_length = 1 + i - word_start_i;
          in_word = FALSE;
          get_substr(word, line, word_start_i, word_length);
          if (col + word_length <= MAX_LINE_COLS) {
            // If word can fit within the current line and doesn't exceed max cols, print it to the current line.
            printf("%s", word);
          } else {
            // Otherwise go to a new line before printing the word.
            printf("\n%s", word);
            // Now start the next line by resetting the col index.
            col = 0;
          }
          // Increase col index by the word we just printed.
          col += word_length;
        }
      } else {
        if (in_word == FALSE) {
          word_start_i = i;
          in_word = TRUE;
        }
      }
    }
    printf("\n");
  } while (length != EOF);
}

void print_col_guide(int max_cols)
{
  char guide[MAX_LENGTH];
  guide[0] = '|';
  for (int i = 1; i < MAX_LINE_COLS - 1; ++i) {
    guide[i] = ' ';
  }
  guide[MAX_LINE_COLS - 1] = '|';
  guide[MAX_LINE_COLS] = '\0';
  printf("%s\n", guide);
}

int get_length(char str[], int include_return)
{
  int i, length;
  i = length = 0;
  while (str[i] != '\0') {
    if (str[i] != '\n' || include_return == TRUE)
      ++length;
    ++i;
  }
  return length;
}

void get_substr(char to[], char from[], int start_i, int length)
{
  int i;
  for (i = 0; start_i + i < start_i + length; ++i) {
    to[i] = from[start_i + i];
  }
  to[i] = '\0';
}

int get_line(char str[], int max_length, int include_return)
{
  // Doesn't seem to be including the return character!!
  int c, i;
  i = 0;
  while ((c = getchar()) != '\n') {
    if (c == EOF) return EOF;
    str[i] = c;
    ++i;
  }
  // Set str[i] to '\n then increment.
  if (include_return == TRUE && c == '\n') str[i++] = '\n';
  // Don't count the terminate char into the string length counter.
  str[i] = '\0';
  return i;
}