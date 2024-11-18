/* count.c
 * Mia Lassiter
 * Sep. 20, 2023
 * This program returns the word count of a text file.
  */

#include <stdio.h>
#include <stdlib.h>
#define MAX_WORD_LENGTH 30

int main (int argc, char* argv[2] ) {
	int counter = 0;
	char word[MAX_WORD_LENGTH];
	FILE *fptr;

	//open file and check that it exists
	fptr = fopen(argv[1], "r");
	if ((fptr == NULL)) {
		printf ("file not found.");
		return;
	}
	
	//scan each word in the file and update the word counter
	while (fscanf(fptr,"%s", word) == 1) {
		counter++;
	}

	printf ("%d total words\n", counter);
	fclose (fptr);
	return 0; 
}
