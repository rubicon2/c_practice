// Exercise 2.6
// Write function setbits(x, p, n, y) that returns x with the n bits that begin at position p set to the rightmost n bits of y, leaving the other bits unchanged.
#include <stdio.h>
#include <stdlib.h>

#define BITS_IN_BYTE 8

typedef unsigned int uint;

uint u_power(const uint base, uint n);
void int_to_bin(int n, char binary[], const int buffer_size);
void uint_to_bin(const uint n, char binary[], const int buffer_size);
uint clear_right_bits(const uint x, const uint bits_to_clear);
uint clear_left_bits(const uint x, const uint bits_to_clear);
uint isolate_bits(const uint x, const uint from, const uint to);
uint setbits(const uint x, const uint y, const uint start_pos, const uint bit_count);

uint u_power(const uint base, uint n)
{
  uint result = 1;
  while (n > 0) {
    result *= base;
    --n;
  }
  return result;
}

void uint_to_bin(uint n, char binary[], const int buffer_size)
{
  // const int bits = sizeof(int) * BITS_IN_BYTE;
  const uint bits = buffer_size - 1;
  int remainder = n;
  for (int i = 0; i < bits; ++i) {
    // See if number fits into binary col, e.g. 63 doesn't fit into 64 but fits into 32...
    uint col_value = u_power(2, bits - 1 - i);
    if (remainder >= col_value) {
      binary[i] = '1';
      remainder -= col_value;
    } else {
      binary[i] = '0';
    }
  }
  binary[buffer_size - 1] = '\0';
  
  if (remainder != 0) {
    fprintf(stderr, "Error: integer could not be converted to binary - not enough bits in buffer\n");
  }
}

uint clear_right_bits(const uint x, const uint bits_to_clear)
{
  // If clear_left_bits or clear_right_bits tries to clear all bits, it ends up being all ones instead of all zeroes?
  // This is undefined behaviour in C. If the bits to clear is the same or higher than the length of the int, just return zero.
  if (bits_to_clear >= sizeof(x) * BITS_IN_BYTE) return 0;
  else return (x >> bits_to_clear) << bits_to_clear;
}

uint clear_left_bits(const uint x, const uint bits_to_clear)
{
  // If clear_left_bits or clear_right_bits tries to clear all bits, it ends up being all ones instead of all zeroes?
  // This is undefined behaviour in C. If the bits to clear is the same or higher than the length of the int, just return zero.
  if (bits_to_clear >= sizeof(x) * BITS_IN_BYTE) return 0;
  else return (x << bits_to_clear) >> bits_to_clear;
}

uint isolate_bits(const uint x, const uint from, const uint to)
{
  const uint left_bits_to_clear = from;
  const uint right_bits_to_clear = sizeof(x) * BITS_IN_BYTE - to;
  return clear_left_bits(clear_right_bits(x, right_bits_to_clear), left_bits_to_clear);
}

uint setbits(const uint x, const uint y, const uint start_bit, const uint bit_count)
{
  // Isolate the bits we want to keep from x.
  uint x_left_bits = isolate_bits(x, 0, start_bit);
  uint x_right_bits = isolate_bits(x, start_bit + bit_count, sizeof(x) * BITS_IN_BYTE);
  // Isolate the last bit_count bits from y.
  uint y_last_bits = isolate_bits(y, sizeof(y) * BITS_IN_BYTE - bit_count, sizeof(y) * BITS_IN_BYTE);
  // Shift the y bits to overlay the x bits we want to overwrite.
  y_last_bits = y_last_bits << (sizeof(x) * BITS_IN_BYTE) - start_bit - bit_count;
  return x_left_bits | y_last_bits | x_right_bits;
}

int main(void)
{
  
  uint x = 0xffffff00;
  uint y = 0xffffffaa;
  uint set = setbits(0xffffff00, 0xffffffaa, 4, 8);

  printf("Overwrite bits 5 - 12 of x with bits 25 - 32 from y:");

  char s[33];
  uint_to_bin(x, s, sizeof(s));
  printf("x: %s\n", s);

  uint_to_bin(y, s, sizeof(s));
  printf("y: %s\n", s);

  uint_to_bin(set, s, sizeof(s));
  printf("r: %s\n", s);
}
