#include <stdio.h>

double fahr_to_celsius(double f);
double celsius_to_fahr(double c);

int main()
{
  int lower_bound = 0;
  int upper_bound = 300;
  int step = 20;
  int current_f;

  printf("F:\tC:\n");
  for (current_f = 0; current_f <= upper_bound; current_f += step) {
    printf("%3d\t%6.2f\n", current_f, fahr_to_celsius(current_f));
  }
}

double fahr_to_celsius(double f)
{
  return (5.0f / 9.0f) * (f - 32.0f);
}

double celsius_to_fahr(double c)
{
  return c / (5.0f / 9.0f) + 32.0f;
}
