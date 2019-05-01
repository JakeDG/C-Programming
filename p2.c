/*
Name: Jacob Gidley
Unix ID: jg236629
Lab Instuctor: Noah Park
Lab Time: Friday @ 12:35

Description:
This program will prompt the user for a mathematical expression. 
The input will be an equation consiting of a string of characters that can include: numbers 0 - 9, +, -, /, *, and spaces.
The expression will be read and calculated from left to right and then the answer will be outputted to the screen. 
*/

#include <stdio.h>

#define SIZE 50 // Size of char array

int main()
{
	char exp[SIZE]; // Stores input expression
	int i,	// Counter
		val = 0, // Value of the expression
		oper = 0; // Used to track operator used
	
	// Get input expression
	printf("Enter expression: ");
	fflush(stdout);
	fgets(exp, SIZE, stdin);

	// Read through input array
	for (i = 0; i < strlen(exp); i++)
	{
		// Check if the array element is an operator
		if (exp[i] == '+')
			oper = 1;

		if (exp[i] == '-')
			oper = 2;

		if (exp[i] == '*')
			oper = 3;

		if (exp[i] == '/')
			oper = 4;
		
		// Check if the array element is a number
		if (exp[i] >= '0' && exp[i] <= '9')
		{
			// Check what operator to use in order to calculate the value

			if (oper == 0) // Initialize value to the first number that's read-in
				val = (exp[i] - '0');

			if (oper == 1)
				val += (exp[i] - '0');

			if (oper == 2)
				val -= (exp[i] - '0');

			if (oper == 3)
				val *= (exp[i] - '0');

			if (oper == 4)
			{
				// Check if dividing by zero
				if (exp[i] != '0')
				{
					val /= (exp[i] - '0');
				}
				else // Output error, Exit program
				{
					printf("Error: divide by zero\n");
					fflush(stdout);
					exit(1);
				}
			}
		}
	}
	
	// Output the answer
	printf("Value = %d\n", val);
	fflush(stdout);

	return 0;
}