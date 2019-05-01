/*
 This program contains review material for the midterm of CEN 333 - Spring 2017
*/

#include <stdio.h>
#include <string.h>
#define SIZE 5
#define WORD_SIZE 30

struct event
{
	char name[100];
	float revenue;
};

int main()
{
	typedef struct event show; // "show" replaces "struct event"
	show b, c;
	typedef char Name[50]; // typedef stuff

	float num = 2.456;
	int x = 1,
		y = 1,
		ans,
		num2 = 456,
		j = 4,
		i,
		numArray[SIZE] = {2,4,6,8,10};
	int **p, *r;
	char word[WORD_SIZE],
		s1 = {"xyzq"},
		s2 = {"abc"},
		*ret,
		word2[14] = {" asshole"};
	Name person = "Bobert";
	r = &x;
	p = &r;

	printf("Address of *r shown with *p: %d\n", *p);
	printf("Value of *r shown with ++**p: %d\n", ++**p);
	printf("Value of *r: %d\n", *r);

	// Formatting
	printf("%5d\n", num2);
	printf("%6.2f\n", num);
	
	// Function calling
	ans = sum(x, y);
	printf("%d\n", ans);

	// Recursion call in printf
	printf("Factorial of %d is %d\n", j, factorial(j));

	// Pass array to function
	printArray(numArray);

	// String stuff
	printf("Enter a word: ");
	scanf("%s", word);

	for (i = 0; word[i] != '\0'; i++)
	{
		printf("%c", word[i]);
	}
	printf("\n");

	strcat(word, word2); // strcat
	ret = strchr(word, 'i'); // strchr
	printf("%s\n", word);
	printf("%s\n", ret);

	// Structure stuff
	show carnival;
	show *struct_pointer; // Stucture pointer declaration
	struct_pointer = &carnival; // Structure pointer initialization

	strcpy(carnival.name, "Chevy Car Show");
	carnival.revenue = 1026.00;

	printf("%s\n", carnival.name);
	printf("$%0.2f\n", struct_pointer->revenue); // Using -> instead of '.' to access the structure member

	strcpy(b.name, "Food show");
	struct_pointer = &b;
	printf("%s\n", (*struct_pointer).name);

	strncpy(s1, s2, 4);
	printf("%s\n", s1);

	return 0;
}

// Function call
int sum(int x, int y)
{
	x += 1;
	y = x + 1;
	return x + y;
}

// Recursion
int factorial(unsigned int i) 
{
	if (i <= 1) 
	{
		return 1;
	}
	return i * factorial(i - 1);
}

// Passing array as arg
int printArray(int *arPtr)
{
	int i;
	for (i = 0; i < SIZE; i++)
	{
		printf("%d ", *arPtr);
		arPtr++;
	}
	printf("\n");
}