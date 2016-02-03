// Project Euler problem #2
// https://projecteuler.net/problem=2
// Solution by Daniel Wood
#include <stdio.h>

int main(void)
{
  int last = 0;
  int next = 1;
  int sum = 0; 

  // While the next term does not exceed 4 million
  while (next <= 4e6)
    {
      // Generate next term in the sequence
      int temp = next;
      next += last;
      last = temp;

      // Sum all even terms
      if (next % 2 == 0)
	sum += next;
    }

  printf ("The sum of all even Fibonacci terms below 4 million is: %d\n", sum);
  return 0;
}
