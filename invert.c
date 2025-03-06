// Exercise 2.7
// Write a function invert(x, p, n) that returns x with the n bits that begin as position p, inverted, leaving others unchanged.
#include <stdio.h>
#include <stdlib.h>

#define BITS_IN_BYTE 8
#define         TRUE 1
#define        FALSE 0

typedef unsigned int uint;


uint create_bit_mask_32(const uint lowest_on_bit, const uint highest_on_bit);
void uint_to_bin(const uint x, char bin[], const uint buffer_size);
uint u_power(const uint base, uint n);
uint invert(const uint x, const uint p, const uint n);

uint create_bit_mask_32(const uint lowest_on_bit, const uint highest_on_bit)
{
  uint mask = 0x00000000;
  for (int bit = lowest_on_bit; bit <= highest_on_bit; ++bit) {
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

void uint_to_bin(const uint x, char bin[], const uint buffer_size)
{
  uint remainder = x;
  uint total_bits = sizeof(x) * BITS_IN_BYTE;
  for (int i = 0; i < buffer_size; ++i) {
    const uint bit_value = u_power(2, total_bits - 1 - i);
    if (remainder >= bit_value) {
      bin[i] = '1';
      remainder -= bit_value;
    } else {
      bin[i] = '0';
    }
  }

  // Don't forget to terminate the string.
  bin[buffer_size - 1] = '\0';

  if (remainder != 0) {
    fprintf(stderr, "Error: the binary buffer is not large enough to represent this number");
    exit(EXIT_FAILURE);
  } 
}

uint invert(const uint x, const uint p, const uint n)
{
  // The rightmost, lowest value bit is 1. The highest is 32.
  const uint bit_mask = create_bit_mask_32(p, p + n - 1);
  return (x & ~bit_mask) | (~x & bit_mask);
}

int main(void)
{
  const uint n = invert(0xf0f0f0f0, 25, 8);
  char s[33];
  uint_to_bin(n, s, sizeof(s));
  printf("%s\n", s);
}
