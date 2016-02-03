// Project Euler problem #1
// https://projecteuler.net/problem=1
// Solution by Daniel Wood

#include <stdio.h>

int main(void)
{
  int sum = 0;

  // Sum all the multiples of 3 or 5, that are below 1000
  for (int i = 3; i < 1000; i++)
    sum += (i % 3 == 0 || i % 5 == 0) ? i : 0;

  printf ("The sum of all the multiples of 3 or 5 below 1000 is: %d\n", sum);
  return 0;
}
