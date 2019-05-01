/*
Name: Jacob Gidley
Unix ID: jg236629
Lab Instuctor: Noah Park
Lab Time: Friday @ 12:35

Description:
This program will prompt the user for a variety of commands and will execute the commands accordingly.
The user will use these commands to create, manipulate, and output a linked list.
Each node of the linked list will have a symbol that is a string of max 10 characters.
Also, each node will have an integer value of count, which stores the amount of times
the same sybol has been inserted. The nodes will be sorted in decreasing order of their counts.
The program will continue to accept and process commands until the user types the "end" command.
*/

// Include headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CMD_SIZE 15		// The length of the whole command including the argument
#define ARG_SIZE 10		// The length of the argument

// Delare linked list using typedef
typedef struct node
{
	char symbol[ARG_SIZE];	// Stores symbol
	int count;				// Stores count value
	struct node *next;		// Node pointer to next node
} Node, *NodePtr;		// Node = struct node, *NodePtr = struct node*

/*
Function: Sort List

Function Description:
Bubblesorts the linked list in decreasing value of each node's count.

Parameter(s):
0: struct node* - The head of the linked list
*/
void sortList(NodePtr head)
{
	int sorted,			// Used to check if list was sorted during the iteration 
		tempCnt;		// Temporarily stores the value of the smaller node count
	NodePtr listItr;	// Used to iterate through the nodes of the list
	char tempSym[ARG_SIZE];		// Temporarily stores the string symbol of the smaller count node

	do
	{
		sorted = 0; // If sorted doesn’t change, then nothing was swapped so the list is sorted and the loop stops.
		listItr = head; // Start at the begining of the list each time

		while (listItr->next != NULL)	// Iterate through the list until the end
		{
			if (listItr->count < listItr->next->count)	// The current node's count is less than the next node's count
			{
				tempCnt = listItr->count;		 // Save count
				strcpy(tempSym, listItr->symbol); // Save symbol

				listItr->count = listItr->next->count;			// Swap the count of the 2nd node into the first
				strcpy(listItr->symbol, listItr->next->symbol); // Swap the symbol 2nd node into the first

				listItr->next->count = tempCnt;			// Store the count of the 1st node into the 2nd
				strcpy(listItr->next->symbol, tempSym); // Store the symbol of the 1st node into the 2nd

				sorted = 1; // Nodes were swapped. Keep sorting.         
			}
			listItr = listItr->next;	// Increment the iterator
		}
	} while (sorted); // Keep sorting until nothing was swapped
}

/*
Function: Insert

Function Description:
Inserts a new node into the linked list unless there exists a node with the same
string symbol as the one the user inputted. If that occurs, then the node with the same string symbol
will have it's count incremented by 1.

Parameter(s):
0: struct node** - The pointer pointing to the head node's values
1: char* - Pointer to the first character in the user's inputted string argument
*/
void insert(NodePtr *head, char *str)
{
	NodePtr listItr = (*head), // Used to iterate through the nodes of the list
		temp;	// Used to allocate memory for linked list and to act as temporary node pointer

	if ((*head) == NULL) // Initial case for creating the first node, or the head of the list
	{
		temp = (NodePtr)malloc(sizeof(Node)); // Allocate memory
		temp->count = 1;			// Initialize the new node's count
		strcpy(temp->symbol, str);	// Initialize the new node's symbol
		temp->next = NULL;			// Point to the end of the list
		(*head) = temp;				// Initalize the head to NULL
		return;
	}

	// Not the end of the list AND the symbols don't match, then iterate through the list
	while (listItr->next != NULL && (strcmp(listItr->symbol, str) != 0))
	{
		listItr = listItr->next;
	}

	if (strcmp(listItr->symbol, str) == 0) // The iterator made it to a symbol that equals str and terminated the loop
	{
		listItr->count++;	// Increment the node's count
		sortList((*head));	// Sort the list
	}
	else // The while loop is terminated because iterator reached the end of the list, and the last node does not contain a symbol equals to str
	{
		temp = (NodePtr)malloc(sizeof(Node));		// Allocate memory
		strcpy(temp->symbol, str);		// Initialize the new node's symbol
		temp->count = 1;				// Initialize the new node's count
		temp->next = NULL;				// Point to the end of the list
		listItr->next = temp;			// Initalize the next node to NULL
	}
}

/*
Function: Delete

Function Description:
Searches if the list contains a node whose symbol is identical to the string specified in the command,
then the count stored in the node is decremented by 1. If the new count becomes 0,
then the node will be removed from the list. If the new count is at least 1, the node will be sorted,
if necessary, to an appropriate position in the list to ensure that the counts are in non-increasing order.
If the symbol is not found then the list is left unchanged.

Parameter(s):
0: struct node** - The pointer pointing to the head node's values
1: char* - Pointer to the first character in the user's inputted string argument
*/
void delete(NodePtr *head, char *str)
{
	NodePtr listItr = (*head),		// Used to iterate through the nodes of the list						
		prevNode;		// Pointer pointing to the node before the list iterator

						// If head node has the symbol that is equal to str
	if (listItr != NULL && (strcmp(listItr->symbol, str) == 0))
	{
		listItr->count--;	// Decrement the count
		if (listItr->count == 0)
		{
			(*head) = listItr->next;	// Move the head position to next node in the list
			free(listItr);            // Clear previous head
		}
		// Sort list if not at the end of the list and the current nodes decremented count is less than the next node's count
		else if (listItr->next != NULL && listItr->count < listItr->next->count)
		{
			sortList((*head));
		}
		return;
	}

	// Traverse list to find the symbol to delete
	while (listItr != NULL && (strcmp(listItr->symbol, str) != 0))
	{
		prevNode = listItr;
		listItr = listItr->next;
	}

	// Return if the symbol was not found
	if (listItr == NULL)
	{
		return;
	}
	else
	{
		listItr->count--; // Decrement the node's count
		if (listItr->count == 0)
		{
			prevNode->next = listItr->next; // Unlink the node from list
			free(listItr);  // clear node
		}
		// Sort list if not at the end of the list and the current nodes decremented count is less than the next node's count
		else if (listItr->next != NULL && listItr->count < listItr->next->count)
		{
			sortList((*head));
		}
	}
}

/*
Function: Forced Delete

Function Description:
Removes each node whose count is less than or equal to the integer value specified by the number the
user's inputted as the argument from the list. If the list is empty or the count stored in each node is greater than
the value specified by the user's input, then the list is left unchanged.

Parameter(s):
0: struct node** - The pointer pointing to the head node's values
1: int - Integer value of the users inputted argument
*/
void forceDelete(NodePtr *head, int num)
{
	NodePtr listItr = (*head),		// Used to iterate through the nodes of the list						
		prevNode;		// Pointer pointing to the node before the list iterator

						// If head node has a count that is less than or equal to num
	if (listItr != NULL && listItr->count <= num)
	{
		(*head) = NULL; // If head has a count value smaller than num, clear all values in the list
		return;
	}

	// Traverse list to find the first node's count that is <= num
	while (listItr != NULL && listItr->count > num)
	{
		prevNode = listItr;
		listItr = listItr->next;
	}

	if (listItr == NULL) // No values >= num are found in the list
	{
		return;
	}
	else
	{
		prevNode->next = NULL; // Deletes all nodes >= num after the previous node
	}
}

/*
Function: Print List

Function Description:
Traverses the list and prints the symbol and the count of each node on a corresponding line by itself.
If the list is empty, then the function prints "The list is empty".

Parameter(s):
0: struct node* - The pointer pointing to the head of the linked list
*/
void printList(NodePtr head)
{
	NodePtr listItr = head; // Used to iterate through the nodes of the list

	if (listItr == NULL)
	{
		printf("\tThe list is empty.\n");
		fflush(stdout);
	}
	else
	{
		while (listItr != NULL)
		{
			printf("\t%s\t%d\n", listItr->symbol, listItr->count);
			fflush(stdout);
			listItr = listItr->next;
		}
	}
}

/*
Function: Print Statistics

Function Description:
Traverses the list and prints amount of nodes in the list, the max count value, the min count value,
and the average count value.
If the list is empty, then the function prints "The list is empty".

Parameter(s):
0: struct node* - The pointer pointing to the head of the linked list
*/
void printStats(NodePtr head)
{
	NodePtr listitr = head;	// Used to iterate through the nodes of the list
	int	nodeNum = 0,	// Stores the amount of nodes in the list
		maxCnt = 0,		// Stores the max count value in the list	
		minCnt = 0;		// Stores the min count value in the list
	float avgCnt = 0;	// Stores the average count in the list

	if (listitr == NULL)	// List is empty
	{
		printf("\tThe list is empty.\n");
		fflush(stdout);
	}
	else
	{
		while (listitr != NULL) // While not at the end of the list
		{
			nodeNum++;								// Increment the amount of nodes counted
			avgCnt = avgCnt + listitr->count;		// Add node's count to average 
			minCnt = listitr->count;	// Store the minimum count
			listitr = listitr->next;
		}

		avgCnt = avgCnt / nodeNum;	// Calculate the average
		maxCnt = head->count;		// Store the max count, which is located at the head of the node

		// Output the statistics of the list
		printf("\tNumber of Nodes: %d\n", nodeNum);
		fflush(stdout);
		printf("\tMax Count: %d\n", maxCnt);
		fflush(stdout);
		printf("\tMin Count: %d\n", minCnt);
		fflush(stdout);
		printf("\tAverage Count: %.2f\n", avgCnt);
		fflush(stdout);
	}
}

/*
Function: Print Prefix

Function Description:
Traverses the list and if the given string str is a prefix of the symbol stored in a node,
then print the symbol and the corresponding count on a line by itself.
If the list is empty, then the function prints "The list is empty".

Parameter(s):
0: struct node* - The pointer pointing to the head of the linked list
1: char* - The prefix the user inputted as an argument
*/
void printPrefix(NodePtr head, char *str)
{
	NodePtr listItr = head;	// Used to iterate through the nodes of the list

	if (listItr == NULL) // List is empty
	{
		printf("\tThe list is empty.\n");
		fflush(stdout);
	}
	else
	{
		while (listItr != NULL)
		{
			if (strncmp(str, listItr->symbol, strlen(str)) == 0) // The value of str matches the first (strlen of str) number of characters in the symbol
			{
				printf("\t%s\t%d\n", listItr->symbol, listItr->count);	// Output node symbol and count
				fflush(stdout);
			}

			listItr = listItr->next;
		}
	}
}

/*
Function: Print Suffix

Function Description:
Traverses the list and if the given string str is a suffix of the symbol stored in a node,
then print the symbol and the corresponding count on a line by itself.
If the list is empty, then the function prints "The list is empty".

Parameter(s):
0: struct node* - The pointer pointing to the head of the linked list
1: char* - The suffix the user inputted as an argument
*/
void printSuffix(NodePtr head, char *str)
{
	NodePtr listItr = head;	// Used to iterate through the nodes of the list
	char *symPtr;	// Used to traverse a node's symbol to help get it's suffix

	if (listItr == NULL)
	{
		printf("\tThe list is empty.\n");
		fflush(stdout);
	}
	else
	{
		while (listItr != NULL)
		{
			// Moves the character pointer to the end of the node's symbol, then moves it back (strlen of str) characters back
			symPtr = listItr->symbol + strlen(listItr->symbol) - strlen(str);

			// If the suffixes are the same then output the node's symbol and count
			if (strncmp(symPtr, str, strlen(str)) == 0)
			{
				printf("\t%s\t%d\n", listItr->symbol, listItr->count);
				fflush(stdout);
			}

			listItr = listItr->next;
		}
	}
}

/*
Function: Print Count Range

Function Description:
Traverses the list and for each node whose count is in the integer range specified by num1 and num2,
the program must print the symbol and the count for that node on a line by itself.
If the list is empty, then the function prints "The list is empty".

Parameter(s):
0: struct node* - The pointer pointing to the head of the linked list
1: int - The first number value the user inputted as an argument
2: int - The second number value the user inputted as an argument
*/
void printRange(NodePtr head, int num1, int num2)
{
	NodePtr listItr = head;		// Used to iterate through the nodes of the list

	if (listItr == NULL) // List is empty
	{
		printf("\tThe list is empty.\n");
		fflush(stdout);
	}
	while (listItr != NULL)
	{
		if (listItr->count >= num1 && listItr->count <= num2) // The value of str matches the first (string length of str) number of characters in the symbol
		{
			printf("\t%s\t%d\n", listItr->symbol, listItr->count);
			fflush(stdout);
		}

		listItr = listItr->next;
	}
}

// Main
int main()
{
	char arg[ARG_SIZE],		// Stores the argument the user enters
		command[CMD_SIZE];	// Stores the command and the argument the user enters

	int numArg1,	// Stores an integer value the user enters
		numArg2;	// Stores an integer value the user enters

	NodePtr head = NULL; // Create empty list

						 // Keep requesting commands until the user enters the "end" command
	while (strcmp(arg, "end"))
	{
		printf("Enter a command: ");
		fflush(stdout);
		fgets(command, 15, stdin); // Reads in the command and argument (cmd arg)
		fflush(stdin);

		sscanf(command, "%s %s", arg, arg);	// Stores the second part of the input string after the first space into arg[]

    // User enters "ins" command
		if (!strncmp(command, "ins", 3))
		{
			insert(&head, arg); // Call insert function
		}

		// User enters "del" command
		if (!strncmp(command, "del", 3))
		{
			delete(&head, arg);	// Call delete function
		}

		// User enters "fde" command
		if (!strncmp(command, "fde", 3))
		{
			sscanf(command, "%s %d\n", &numArg1, &numArg1);	// Read in number argument
			forceDelete(&head, numArg1); // Call insert function
		}

		// User enters "prl" command
		if (!strncmp(command, "prl", 3))
		{
			printList(head); // Call print list function
		}

		// User enters "pst" command
		if (!strncmp(command, "pst", 3))
		{
			printStats(head); // Call print statistics function
		}

		// User enters "ppr" command
		if (!strncmp(command, "ppr", 3))
		{
			printPrefix(head, arg); // Call print prefix function
		}

		// User enters "psu" command
		if (!strncmp(command, "psu", 3))
		{
			printSuffix(head, arg); // Call print suffix function
		}

		// User enters "pcr" command
		if (!strncmp(command, "pcr", 3))
		{
			sscanf(command, "%s %d %d\n", &numArg1, &numArg1, &numArg2); // Read in number arguments
			printRange(head, numArg1, numArg2); // Call print count range function
		}
	}
	return 0;
}