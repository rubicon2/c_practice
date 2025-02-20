// Exercise 2.1 - determine ranges of signed and unsigned char, short, int, long.
#include <stdio.h>
#include <math.h>

#define BITS_IN_BYTE 8

struct Range {
  double min;
  double max;
};

int power(int base, int n);
double d_power(int base, int n);
void print_range(char name[], struct Range range);

int power(int base, int n)
{
  int result = 1;
  while (n > 0) {
    result *= base;
    --n;
  }
  return result;
}

// For results that are too big to fit in an int.
double d_power(int base, int n)
{
  double result = 1;
  while (n > 0) {
    result *= base;
    --n;
  }
  return result;
}

struct Range get_unsigned_range(int type_size_bytes)
{
  struct Range range = {
    .min = 0,
    .max = d_power(2, type_size_bytes * BITS_IN_BYTE) - 1
  };
  return range;
}

struct Range get_signed_range(int type_size_bytes)
{
  double type_max = d_power(2, type_size_bytes * BITS_IN_BYTE) - 1;
  struct Range range = {
    // This should be -128 for char, but gives -127... not flooring as expected.
    // Was due to type_max / 2 - arithmetic with ints automatically truncates the decimal! 
    // Divide by float to get a float result instead of a truncated int result.
    .min = floor(0 - type_max / 2.0f),
    .max = floor(type_max / 2.0f)
  };
  return range;
}

void print_range(char name[], struct Range range)
{
  printf("%s:\t%15.f %15.f\n", name, range.min, range.max);
}

int main(void)
{
  struct Range unsigned_char = get_unsigned_range(sizeof(char));
  struct Range signed_char = get_signed_range(sizeof(char));

  struct Range unsigned_short = get_unsigned_range(sizeof(short));
  struct Range signed_short = get_signed_range(sizeof(short));

  struct Range unsigned_int = get_unsigned_range(sizeof(int));
  struct Range signed_int = get_signed_range(sizeof(int));

  struct Range unsigned_long = get_unsigned_range(sizeof(long));
  struct Range signed_long = get_signed_range(sizeof(long));

  struct Range unsigned_float = get_unsigned_range(sizeof(float));
  struct Range signed_float = get_signed_range(sizeof(float));

  printf("Unsigned\n");
  print_range("  char", unsigned_char);
  print_range(" short", unsigned_short);
  print_range("   int", unsigned_int);
  print_range("  long", unsigned_long);

  printf("\nSigned\n");
  print_range("  char", signed_char);
  print_range(" short", signed_short);
  print_range("   int", signed_int);
  print_range("  long", signed_long);
}
