/*
Name: Jacob Gidley
Unix ID: jg236629
Lab Instuctor: Noah Park
Lab Time: Friday @ 12:35

Description:
This program will prompt the user for two integers. The first input number will be a positive decimal value, while the second input number will be the radix. The radix will be assumed to be either of the numbers 2-16. The first inputted number will then be converted into the appropriate base determined by the radix and outputted to the screen.
*/

#include <stdio.h>

#define SIZE 32 // Size of char array

int main()
{
	int dec, // Decimal
		rad, // Radix
		quot = 1, // Quotient
		rem = 0, // Remainder
		i = 0;  // Counter
	char c[SIZE]; // Stores the converted decimal

				  // Prompt and get input from user
	printf("Enter two integers: ");
	fflush(stdout);
	scanf("%d%d", &dec, &rad);

	// Convert decimal to the radix base
	while (quot != 0)
	{
		quot = dec / rad; // Get the quotient
		rem = dec % rad; // Get the remainder
		dec = quot;

		// Check to see if quotient needs to be converted into a letter
		if (rem > 9)
		{
			c[i] = rem + 55; // Add 55 to get ASCII value of letter
		}
		else
		{
			c[i] = rem + '0';
		}

		i++;
	}

	// Output the converted decimal
	printf("Answer = ");
	fflush(stdout);
	for (i = (i - 1); i >= 0; i--)
	{
		printf("%c", c[i]); // Print the char array
		fflush(stdout);
	}
	printf("\n");
	fflush(stdout);

	return 0;
}