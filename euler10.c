#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

// Memory-saving sieve of Eratosthenes
// Bit operations not optimized
int main(int argc, char *argv[])
{
  if (argc < 2)
    {
      fprintf(stderr, "Usage:\n\t%s <N-primes> "
	              "[<multi=1.2f> <outfile>]\n"
	              "\tA negative N will be used as limit."
	              "\n\n", argv[0]);
      return -1;
    }

  int32_t i, j, k;    // Iterators
  int32_t max;        // argv[1]
  uint32_t n, sqrtn;  // Sieve limit / cached sqrt(n)
  uint32_t nwords;    // Size of buffer (in words)
  FILE *outfile = stdout;

  // 1 over 32
  const float _1_bits = 1.f / 32.f;

  // Safety multiplier on prime estimate
  double multi = 1.2f;
  if (argc > 2)
    {
      multi = fabs(strtod(argv[2], NULL));
      if (multi == .0f)
	{
	  fprintf(stderr, "Invalid float value: \"%s\"\n", argv[2]);
	  return -1;
	}
    }

  // Estimate n-th prime from argv[1]
  max = strtol(argv[1], NULL, 0);
  if (max > 3)
    n = (int)((max * (logf(max) + logf(logf(max - 1)))) * multi);
  else
  if (max != 0)
    {
      n = max = abs(max);
    }
  else
    {
      fprintf(stderr, "N cannot be 0\n");
      return -1;
    }

  sqrtn = ceilf(sqrt(n));
  
  // Open output file
  if (argc > 3)
    if ((outfile = fopen(argv[3], "w")) == NULL)
      {
	fprintf(stderr, "Unable to open file: %s\n", argv[3]);
	return -1;
      }
  
  // Number of words needed to store N-bits
  nwords = ceilf((float)n * _1_bits);

  // Format memory
  char unit[] = "BKMG";
  for (i = 0; unit[i] != '\0'; i++)
    if (nwords * 4 <= pow(1024, i + 1))
      break;
  
  // Memory info
  fprintf(outfile, "Sieve limit at: %d\n"
	           "Size of buffer: %.1f%c\n",
	           n, (nwords * 4) / pow(1024, i), unit[i]);

  // Buffers
  uint32_t nbuf[nwords];   // Bit-array for sieve
  uint32_t primes[max+1];  // Integer array to store primes
  uint32_t *p;             // Prime pointer (for faster access?)

  // Fill buffer with set bits
  for (j = 0; j < nwords; j++)
    nbuf[j] = 0xFFFFFFFF;

  // Cross out the twos
  for (i = 3; i < n; i += 2)
    {
      j = floor((float)i * _1_bits);
      nbuf[j] &= ~(1 << i % 32);
    }
  
  // Cross out the rest
  for (i = 2; i < sqrtn; i += 2)       // i = bit (starts at 3)
    {
      j = floor((float)i * _1_bits);   // j = current byte
      
      // Check bit
      if ((nbuf[j] >> i % 32) & 1)
	{
	  // Unset all multiples
	  k = i + (i + 1);             // k = multiples of i
	  for (; k < n; k += i + 1)
	    {
	      j = floor((float)k * _1_bits);

	      // Unset bit
	      nbuf[j] &= ~(1 << k % 32);
	    }
	}
    }

  // Filter primes into their own array
  for (i = j = k = 0; i < n; i++)
    {
      j = floor((float)i * _1_bits);
      if ((nbuf[j] >> i % 32) & 1)
	{
	  primes[k++] = i + 1;

	  if (k >= max)
	    break;
	}
    }

  // Output primes
  uint64_t sum = 0;
  for (p = primes, i = 0; i < k; sum += *p, p++, i++)
    fprintf(outfile, "%u\n", *p);

  fprintf(outfile, "Sum: %llu\n", sum);
  
  // Clean up outfile
  if (outfile != stdout)
    fclose(outfile);
  
  return 0;
}
