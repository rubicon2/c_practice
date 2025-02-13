#include <stdio.h>

#define  TRUE 1
#define FALSE 0

// Create a vertical histogram (bar chart) showing the lengths of words in the input.
int main()
{
  int c, i, current_word_length, in_word;
  // Count words from "1 letter" to "10 letters or more".
  int word_lengths_count[10];

  for (i = 0; i < 10; ++i) {
    word_lengths_count[i] = 0;
  }

  current_word_length = 0;
  in_word = FALSE;
  while ((c = getchar()) != EOF) {
    if (c == ' ' || c == '\t' || c == '\n') {
      // Array has only 10 elements so limit any word lengths. If it is 10 chars or over, lump together as 10+.
      if (current_word_length > 10) current_word_length = 10;
      if (current_word_length > 0) {
        ++word_lengths_count[current_word_length - 1];
      }
      current_word_length = 0;
      in_word = FALSE;
    } else {
      ++current_word_length;
      in_word = TRUE;
    }
  }

  // Find maximum value in the array so we know how many lines to iterate through for the rows of the bar chart.
  int highest_word_length = 0;
  for (i = 0; i < 10; ++i) {
    if (word_lengths_count[i] > highest_word_length)
      highest_word_length = word_lengths_count[i];
  }

  int x, y;
  // For each row of the chart - start at the top then go to the bottom.
  for (y = highest_word_length; y > 0; --y) {
    // For each column.
    printf("%2d >", y);
    int x;
    for (x = 0; x < 10; ++x) {
      // If the height of this column is greater than or equal to this row, print a bar, otherwise blank space.
      int col_bar_height = word_lengths_count[x];
      if (col_bar_height >= y)
        printf("|`| ");
      else 
        printf("    ");
    }
    printf("\n");
  }
  printf("    -1---2---3---4---5---6---7---8---9--10+\n");
  printf("x axis: word length, y axis: word count");
}
