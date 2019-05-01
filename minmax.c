#include <stdio.h>

#define SIZE 3 // Array size

int main()
{
	int input[SIZE], 
		i, 
		choice, 
		min, 
		max;
	
	// Get input
	for (i = 0; i < SIZE; i++)
	{
		printf("Enter a number: ");
		fflush(stdout);
		scanf("%d", &input[i]);
	}

	// Initialize min and max
	min = input[0];
	max = input[0];
	
	// Prompt user for min or mox
	printf("Would you like to find the min or max value?\nEnter 1 or 2: ");
	scanf("%d", &choice);

	if (choice == 1) // Min
	{
		for (i = 1; i < SIZE; i++)
		{
			if (input[i] < min)
			{
				min = input[i];
			}
		}

		printf("Min: %d\n", min); // Output min
	}
	else // Max
	{
		for (i = 1; i < SIZE; i++)
		{
			if (input[i] > max)
			{
				max = input[i];
			}
		}

		printf("Max: %d\n", max); // Output max
	}

	return 0;
}