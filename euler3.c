// Project Euler problem #3
// https://projecteuler.net/problem=3
// Solution by Daniel Wood
#include <stdio.h>
#include <math.h>

int main(void)
{
  const int LIMIT = 300000;         // Limit sieve at 30k
  const long long n = 600851475143; // Number for factorization

  // The stack can take 30k * 4 (* 2)
  int candidates[LIMIT];
  int primes[LIMIT];
  
  // Iterators
  int i, j;
  
  // 2 ... n+2
  for (i = 0; i < LIMIT; i++)
    candidates[i] = i + 2;

  // Sieve of Eratosthenes
  for (i = 0; i < LIMIT; i++)
    if (candidates[i] != -1)
      {
	j = candidates[i] * 2 - 2;
	for (; j < LIMIT; j += candidates[i])
	  candidates[j] = -1;
      }

  // Primes in their own array
  for (i = j = 0; i < LIMIT; i++)
    if (candidates[i] != -1)
      primes[j++] = candidates[i];

  // Trial division from largest prime down
  for (; j > 0; j--)
    {
      double quotient = (double)n / (double)primes[j];
      if (fabs(quotient - floor(quotient)) <= 1.e-16f)
	{
	  printf("The largest prime factor of %lld is: %d\n", n, primes[j]);
	  return 0;
	}
    }

  return 1;
}
