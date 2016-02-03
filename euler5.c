// Project Euler problem #5
// https://projecteuler.net/problem=5
// Solution by Daniel Wood
#include <stdio.h>
#include <math.h>

// Give up after a billion iterations (short scale)
const long max_iter = 1e9;

int main(void)
{
  long long i;
  int j;
  int success;
  
  // Slow trial division
  for (i = 20; i <= max_iter; i++)
    {
      success = 1;
      for (j = 2; j <= 20 && success; j++)
	{
	  double res = (double)i / (double)j;
	  if (res > floor(res))
	    success = 0;
	}

      // Output answer in case of a success
      if (success)
	{
	  printf("The smallest positive integer, that is evenly divisible by 1-20 is: %lld\n", i);
	  return 0;
	}
    }

    return 1;
}
