// Exercise 2.9
// In a two's complement number system, x &= (x - 1) deletes the rightmost bit in x. Explain why.
// Use this observation to write a faster version of bitcount.
// The last bit is turned to zero. Due to the subtraction, lower-value bits will be turned to 1s.
// Then the bitwise & operation removes them all. In the end this just removes the rightmost bit.
// E.g. 1010 (10) - 1 = 1001 (9). 1010 & 1001 = 1000 (8).
#include <stdio.h>
#include <time.h>

int bitcount(unsigned x);
int bitcount_fast(unsigned x);

int bitcount(unsigned x)
{
  int b;
  for (b = 0; x != 0; x >>= 1) {
    if (x & 01)
      ++b;
  }
  return b;
}

int bitcount_fast(unsigned x) {
  int b = 0;
  while (x > 0) {
    x &= (x - 1);
    ++b;
  }
  return b;
}

int main(void)
{
  unsigned x = 0xffffffff;

  clock_t timer;

  timer = clock();
  int bit_count = bitcount(x);
  timer = clock() - timer;

  printf("regu: %d, %dms\n", bit_count, ((float)timer) / CLOCKS_PER_SEC);

  timer = clock();
  bit_count = bitcount_fast(x);
  timer = clock() - timer;
  printf("fast: %d, %dms\n", bit_count, ((float)timer) / CLOCKS_PER_SEC);
}
