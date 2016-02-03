// Project Euler problem #6
// https://projecteuler.net/problem=6
// Solution by Daniel Wood
#include <stdio.h>

int main(void)
{
  int sumsquares = 0;
  int squaredsum = 0;

  // Iterate all natural numbers up to (and including) 100
  for (int i = 1; i <= 100; i++)
    {
      squaredsum += i;     // Sum the numbers
      sumsquares += i * i; // Sum their squares
    }

  // Square the sum
  squaredsum *= squaredsum;

  // Using a few lines to remain verbose
  printf("The sum of all squared natural numbers up to 100 is: %d\n", sumsquares);
  printf("The squared sum of all natural numbers up to 100 is: %d\n", squaredsum);
  printf("The difference between these two sums is: %d\n", squaredsum - sumsquares);
  
  return 0;
}
