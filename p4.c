/*
Name: Jacob Gidley
Unix ID : jg236629
Lab Instuctor : Noah Park
Lab Time : Friday @ 12:35

Description :
This program will ...
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFERSIZE 80

typedef struct node // holds an identifiers line numbers
{
	int on_line;
	struct node *next;
} Node, *NodePtr;

typedef struct id
{
	char identifier[11];
	int lineNum;
	struct node *head;		// Pointer to the linked list that holds the identifiers line numbers
} Id;

// Insert line numbers
void insert(Id *id, int ln)
{
	printf("insert %d\n", ln);
	NodePtr listItr, // Used to iterate through the nodes of the list
		temp;	// Used to allocate memory for linked list and to act as temporary node pointer
	if (id->head == NULL) // Initial case for creating the first node, or the head of the list
	{
		printf("head is null\n");
		temp = (NodePtr)malloc(sizeof(Node)); // Allocate memory
		temp->on_line = ln;			// Initialize the new node's line number
		temp->next = NULL;			// Point to the end of the list
		id->head = temp;				// Initalize the head to NULL
		return;
	}
	listItr = id->head;
	// Not the end of the list AND the symbols don't match, then iterate through the list
	while (listItr->next != NULL)
	{
		listItr = listItr->next;
	}

	temp = (NodePtr)malloc(sizeof(Node));		// Allocate memory
	temp->on_line = ln;				// Initialize the new node's line number
	temp->next = NULL;				// Point to the end of the list
	listItr->next = temp;			// Initalize the next node to NULL
}

void crossRef(FILE *inf, FILE *outf)
{
	char buffer[BUFFERSIZE];
	char *token;
	Id idArray[100];
	int i = 0, line = 1, idArrCnt = 0;

	//printf("Before while loop,  line value = %d  \n", line);
	while (fgets(buffer, BUFFERSIZE, inf) != NULL)
	{
		if (isBlankOrCom(buffer) != -1) // Line is not blank
		{
			token = strtok(buffer, " ");
			//printf(outf, "%s ", token);
			//printf("Before token while loop,  Line = %d   \n", line);
			while (token != NULL)
			{
				//printf("Temp: %s\n", token);

				if (strchr(token, '#')) // Detect if a comment in the middle of line, if found, skip to the next line and increment line number.
				{
					//printf("comment if-test, line value = %d   \n", line);
					break;
				}
				else if (strchr(token, ':') && strchr(token, '\"') == NULL) //if the token is an identifier, so add to array of structs
				{
					//printf("Token: %s, Length: %d\n", token, strlen(token));
					token[strlen(token) - 1] = 0; //remove colon
					strcpy(idArray[i].identifier, token); // Copy the token into the identifier field
					idArray[i].lineNum = line; // store declared line number
											   //printf("Array ident: %s Line #: %d\n", idArray[i].identifier, idArray[i].lineNum);
					idArray[i].head = NULL;
					idArrCnt++;
					i++;
					//printf("identifier if-test, line value = %d   \n", line);
				}
				else
				{
					// check if the token contains one of the identifiers already found.
					for (i = 0; i < idArrCnt; i++)
					{
						printf("token: %s, TOK: %s\n", idArray[i].identifier, token);
						if (strstr(token, idArray[i].identifier)) //<<--------- This is not working
						{
							printf("Attempting insert\n");
							insert(&idArray[i], line); //Add the line number to the list in idArray[index]
						}
					}
				}
				//printf("%s ", token);
				token = strtok(NULL, " ");
			}
			line++;
			//printf("\n");
		}
	}
	printf("Cross Reference Table\n");
	printf("\nIdentifier\tDefinition\tUse\n\n");
	for (i = 0; i < idArrCnt; i++)
	{
		printf("%s\t\t%d\t\t", idArray[i].identifier, idArray[i].lineNum);
		while (idArray[i].head != NULL)
		{
			printf("%d ", (idArray[i].head)->on_line);
			idArray[i].head = (idArray[i].head)->next;
		}
		printf("\n");
	}
}

void listFile(FILE *inf, FILE *outf)
{
	char buffer[BUFFERSIZE];
	int line = 1;

	while (fgets(buffer, BUFFERSIZE, inf) != NULL)
	{
		if (isBlankOrCom(buffer) != -1) // Check if line is blank or contains only whitespaces
		{
			fprintf(outf, "%d %s", line, buffer); // Print line with line number
		}
		else
		{
			fprintf(outf, "%s", buffer); // Print blank line without line number
		}
		line++;
	}

	// Close the files
	fclose(inf);
	fclose(outf);
}

// Copies the input file to output as well as the cross-refernce table
void crossList(FILE *inf, FILE *outf)
{
	char buffer[BUFFERSIZE];
	int line = 0;

	while (fgets(buffer, BUFFERSIZE, inf) != NULL)
	{
		if (isBlankOrCom(buffer) != -1) // Check if line is blank or contains only whitespaces
		{
			fprintf(outf, "%d %s", ++line, buffer); // Print line with line number
		}
		else
		{
			fprintf(outf, "%s", buffer); // Print blank line without line number
		}
	}

	// Cross reference table to be added before files are closed.

	// Close the files
	fclose(inf);
	fclose(outf);
}

// Returns -1 if line contains only whitespace chars or is empty, 1 if a comment line, 0 if not a blank line
int isBlankOrCom(char *lp)
{
	// Iterate through each character.
	while (*lp != '\n')
	{
		if (!isspace(*lp) && *lp != '#')
		{
			// Found the non-whitespace and non-comment(#) character.
			return 0;
		}
		if (!isspace(*lp) && *lp == '#')
		{
			return 1; // Found a non-whitespace and a comment(#) character.
		}
		lp++;
	}
	return -1; // Line is blank
}

int main(int argc, char *argv[])
{
	NodePtr head = NULL; // Create empty list
	FILE *infp, *outfp; // Initialize input file pointer

	if ((infp = fopen(argv[2], "r")) == NULL) // File open failed.
	{
		printf("Can’t open %s\n", argv[2]);
		exit(1);
	}

	if ((outfp = fopen(argv[3], "w")) == NULL) // File open failed.
	{
		printf("Can’t open %s\n", argv[3]);
		exit(1);
	}

	// Check flags
	if (strcmp(argv[1], "-l") == 0) // List file
	{
		printf("%s Flag Detected\n", argv[1]);
		listFile(infp, outfp);
	}

	if (strcmp(argv[1], "-c") == 0) // Cross reference table
	{
		printf("-c Flag: %s\n", argv[1]);
		crossRef(infp, outfp);
	}

	if (strcmp(argv[1], "-b") == 0)
	{
		printf("-b Flag: %s\n", argv[1]);
		crossList(infp, outfp);
	}

	return 0;
}