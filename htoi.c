// Exercise 2.3
// Write the function htoi(s), which converts a string of hex digits 
// (including an optional 0x), into its equivalent integer value.
#include <stdio.h>
#include <stdlib.h>

#define LOWER_CASE_START 97
#define UPPER_CASE_START 65

void to_upper_case(char s[]);
void to_lower_case(char s[]);
int str_len(const char s[]);
int htoi(char s[]);

void to_upper_case(char s[])
{
  int c, i;
  i = 0;
  while ((c = s[i]) != '\0') {
    if (c >= 'a' && c <= 'z') {
      s[i] = c - (LOWER_CASE_START - UPPER_CASE_START);
    }
    ++i;
  }
}

void to_lower_case(char s[])
{
  int c, i;
  i = 0;
  while ((c = s[i]) != '\0') {
    if (c >= 'A' && c <= 'Z') {
      s[i] = c + (LOWER_CASE_START - UPPER_CASE_START);
    }
    ++i;
  }
}

int str_len(const char s[])
{
  int i = 0;
  while (s[i] != '\0')
    ++i;
  return i;
}

int power(const int base, int n)
{
  int result = 1;
  while (n > 0) {
    result *= base;
    --n;
  }
  return result;
}

int htoi(char s[]) {
  // Convert hex to lower case so we don't have to worry about lower/upper case hex values.
  to_lower_case(s);
  int length = str_len(s);
  int result = 0;
  for (int i = length - 1; i >= 0; --i) {
    char c = s[i];
    // We are going from right to left - if we reach the optional 0x prefix, leave the loop.
    if (c == 'x') break;
    int char_value = 0;
    if (c >= 'a' && c <= 'f') {
      char_value = 10 + c - 'a';
    } else if (c >= '0' && c <= '9') {
      char_value = c - '0';
    } else {
      fprintf(stderr, "Error: attempted to convert a non-hex character: %c\n", c);
      exit(1);
    }
    // char_value (e.g. 0 - 9, then A = 10 - F = 15) multipled by 16 to the power 
    // of the column we are in. Rightmost col is zero, hence subtracting 1.
    result += char_value * power(16, length - i - 1);
  }
  return result;
}

int main(void)
{
  char hex[] = "0xb3ad";
  int converted = htoi(hex);
  printf("Hex:\t%s,\tInt:\t%d\n", hex, converted);
}
