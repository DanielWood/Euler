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
	              "\tA negative N will be used (absolute) as the limit of the sieve.\n", argv[0]);
      return -1;
    }

  // i = bit counter, j = byte, k = bit offset, l = multiples of i
  int i, j, k, l;
  int max;
  int n, nbytes;
  const float _1_bits = 1.f / 8.f;
  FILE *outfile = stdout;

  // Safety multiplier on prime estimate
  double multi = 1.2f;
  if (argc > 2)
    {
      multi = fabs(strtod(argv[2], NULL));
      if (multi < 1.e-16)
	{
	  fprintf(stderr, "Invalid float value: \"%s\"\n", argv[2]);
	  return -1;
	}
    }

  // Estimate n-th prime from argv[1]
  max = strtol(argv[1], NULL, 0);

  if (max < 0)
    {
      printf("Detected negative max, using as limit instead\n");
      n = max = abs(max);
    }
  else
    n = (int)((max * (logf(max) + logf(logf(max - 1)))) * multi); 
  
  // Open output file
  if (argc > 3)
    if ((outfile = fopen(argv[3], "w")) == NULL)
      {
	fprintf(stderr, "Unable to open file: %s\n", argv[3]);
	return -1;
      }
  
  // Number of bytes needed to hold n-bits
  nbytes = ceilf((float)n * _1_bits);
  printf("n:\t%d\nnbytes:\t%d\n", n, nbytes);

  // Sieve buffers
  uint8_t nbuf[nbytes];    // Bit-array for sieve
  uint32_t primes[max];    // Integer array to store primes

  // Fill buffer with set bits
  for (j = 0; j < nbytes; j++)
    nbuf[j] = 0xFF;

  // Sieve
  for (i = 1; i < n; i++)              // i = bit (starts at 2)
    {
      j = floor((float)i * _1_bits);   // j = target byte
      k = i % 8;                       // k = bit offset from j

      // Check bit
      if ((nbuf[j] >> k) & 1)
	{
	  // Unset all multiples
	  l = i + (i + 1);             // l = multiples of i
	  for (; l < n; l += i + 1)
	    {
	      j = floor((float)l * _1_bits);
	      k = l % 8;

	      // Unset bit l
	      nbuf[j] &= ~(1 << k);
	    }
	}
    }

  // Filter and feed primes into their own array
  for (i = j = l = 0; i < n; i++)
    {
      j = floor((float)i * _1_bits);
      k = i % 8;
      if ((nbuf[j] >> k) & 1)
	{
	  primes[l++] = i + 1;

	  if (l >= max)
	    break;
	}
    }

  // Output primes
  uint64_t sum = 0;
  for (i = 0; i < l; i++, sum += primes[i])
    {
      fprintf(outfile, "Prime #%d\t=\t%u\n", i + 1, primes[i]);
    }
  
  fprintf(outfile, "Sum of primes: %llu\n", sum-1);
  
  // Clean up outfile
  if (outfile != stdout)
    fclose(outfile);
  
  return 0;
}



