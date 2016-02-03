// Project Euler problem #4
// https://projecteuler.net/problem=4
// Solution by Daniel Wood
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
  char test[8];
  int is_palindrome;
  int top_product = 0;

  // Brute-force every combination of three digit numbers
  for (int a = 100; a < 1000; a++)
    for(int b = 100; b < 1000; b++)
      {
	// Calculate their product
	int product = a * b;
	snprintf(test, 8, "%d", product);    // Convert it to a string

	// Check if the string is a palindrome
	is_palindrome = 1;
	for (int i = 0, max = strlen(test); i < max / 2; i++)
	  if (test[i] != test[max - 1 - i])
	    is_palindrome = 0;

	// Save the highest palindromic product
	if (is_palindrome && product > top_product)
	  top_product = product;
      }

  printf("The highest palindromic product of two 3-digit numbers is: %d\n", top_product);
  
  return 0;
}
