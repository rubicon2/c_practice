#include <stdio.h>

// 0 - 9 = 48 to  57
// a - z = 97 to 122
// A - Z = 65 to  90

void print_h_bar(int length);
void print_h_divider(int length);

int main()
{
  int c, i, x, y, highest_bar;
  int alpha_count[26], number_count[10];

  for (i = 0; i < 10; ++i) {
    number_count[i] = 0;
  }

  for (i = 0; i < 26; ++i) {
    alpha_count[i] = 0;
  }

  while ((c = getchar()) != EOF) {
    // If c is a lowercase char, move to uppercase so we don't have to deal with both upper and lowercase characters.
    if (c >= 97 && c <= 122) c -= 32;
    if (c >= 65 && c <= 90) ++alpha_count[c - 'A'];
    if (c >= 48 && c <= 57) ++number_count[c - '0'];
  }

  highest_bar = 0;
  for (i = 0; i < 10; ++i) {
    if (number_count[i] > highest_bar) 
      highest_bar = number_count[i];
  }

  for (i = 0; i < 26; ++i) {
    if (alpha_count[i] > highest_bar)
      highest_bar = alpha_count[i];
  }

  for (y = 0; y < 10; ++y) {
    printf("%c:|", y + '0');
    int bar_length = number_count[y];
    print_h_bar(bar_length);
  }

  // Line dividing the types.
  // This accounts for the labelling of the y axis and the number at the end of each bar.
  print_h_divider(highest_bar * 2 + 4);

  for (y = 0; y < 26; ++y) {
    printf("%c:|", y + 'A');
    int bar_length = alpha_count[y];
    print_h_bar(bar_length);
  }
}

void print_h_bar(int length)
{
  for (int x = 0; x < length; ++x) {
    printf("-|");
  }

  if (length > 0) printf("%d", length);
  printf("\n");
}

void print_h_divider(int length)
{
  for (int x = 0; x < length; ++x) {
    printf("-");
  }
  printf("\n");
}
