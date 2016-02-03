#include <stdio.h>

#define LIMIT 150000
#define PRIME 10001

// Project Euler Challenge 7
int main(void)
{
  int i, j;
  int top, primes = 0;
  int candidates[LIMIT];

  // Candidates: 2 ... n
  for (i = 0; i < LIMIT; i++)
    candidates[i] = i + 2;

  // Sieve of Eratosthenes
  for (i = 0; i < LIMIT; i++)
    if (candidates[i] != -1)
      {
	j = 2 * candidates[i] - 2;
	for (; j < LIMIT; j += candidates[i])
	  candidates[j] = -1;
      }

  // Output primes
  for (i = 0; i < LIMIT; i++)
    if (candidates[i] != -1 && (top = candidates[i]))
	if (++primes == PRIME)
	  {
	    printf("Answer: %d\n", candidates[i]);
	    return 0;
	  }

  // Tell us what went wrong
  fprintf(stderr, "Couldn't reach prime: %d\t"
	          "(Highest: %d [%d])\n",
	          PRIME, primes, top);
  fprintf(stderr, "Limit is too low: %d\n", LIMIT);
  
  return 1;
}




