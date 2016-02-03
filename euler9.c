#include <stdio.h>

const int max_iter = 1.e3;

// Project Euler Challenge 9
int main(void)
{
  long long a, b, c;
  for (a = 3; a < max_iter; a++)
    for (b = 4; b < max_iter; b++)
      for (c = 5; c < max_iter; c++)
	if (a*a + b*b == c*c)
	  {
	    int a1 = a;
	    int b1 = b;
	    int c1 = c;

	    while (a1 + b1 + c1 < 1000)
	      {
		a1 *= 2;
		b1 *= 2;
		c1 *= 2;
	      }

	    if (a1 + b1 + c1 == 1000)
	      {
		printf("Answer: %d\n", a1*b1*c1);
		return 0;
	      }
	  }
  
  return 0;
}
