// Exercise 2.8
// Write a function rightrot(x, n) that returns the value of the integer x rotated to the right by n bit positions.
// The bits shifted off one end end are plopped onto the other end.
#include <stdio.h>
#include <stdlib.h>

#define BITS_IN_BYTE 8
#define         TRUE 1
#define        FALSE 0

typedef unsigned int uint;

uint create_bit_mask_32(const uint first_on_bit, const uint last_on_bit);
uint u_power(const uint base, uint n);
void uint_to_bin(const uint x, char bin[], const int buffer_size);

uint create_bit_mask_32(const uint first_on_bit, const uint last_on_bit)
{
  uint mask = 0x00000000;
  for (int bit = first_on_bit; bit <= last_on_bit; ++bit) {
    mask |= 1 << (bit - 1);
  }
  return mask;
}

uint u_power(const uint base, uint n)
{
  uint result = 1;
  while (n > 0) {
    result *= base;
    --n;
  }
  return result;
}

void uint_to_bin(const uint x, char bin[], const int buffer_size)
{
  const uint total_bits = sizeof(x) * BITS_IN_BYTE;
  uint remainder = x;
  for (int i = 0; i < buffer_size; ++i) {
    const uint bit_value = u_power(2, total_bits - i - 1);
    if (remainder >= bit_value) {
      bin[i] = '1';
      remainder -= bit_value;
    } else {
      bin[i] = '0';
    }
  }

  bin[buffer_size - 1] = '\0';

  if (remainder != 0) {
    fprintf(stderr, "Error: there are not enough bits to represent this number: %d\n", x);
    exit(EXIT_FAILURE);
  }
}

uint rightrot(const uint x, const uint n)
{
  uint x_word_length = sizeof(x) * BITS_IN_BYTE;
  // Get a copy of the rightmost bits before they are shifted off the end and lost.
  // Masking the bits is unnecessary since when we shift it to the left, the rightmost bits will be filled with zeroes.
  uint shifted_off_bits = x & create_bit_mask_32(1, n);
  // Shift the lost bits over to the leftmost side of the word.
  shifted_off_bits = shifted_off_bits << x_word_length - n;
  // Shift all x's bits right, leaving zeroes on the leftmost bits.
  uint shifted_x = x >> n;
  // Composite the shifted version of x with the shifted off bits!
  return shifted_x | shifted_off_bits;
}

uint rightrot_simple(const uint x, const uint n)
{
  // This takes advantage of the fact that bit shifting fills the empty bits with zeroes.
  return (x >> n) | (x << ((sizeof(x) * BITS_IN_BYTE) - n));
}

int main(void)
{
  uint x = 0xff00ffaa;
  uint x_rotated_right = rightrot_simple(x, 4);

  char s[33];
  uint_to_bin(x, s, sizeof(s));
  printf("%s\n", s);

  uint_to_bin(x_rotated_right, s, sizeof(s));
  printf("%s\n", s);
}
