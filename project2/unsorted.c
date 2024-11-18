/*Mia Lassiter
COEN 12 
Project 2: Unsorted set

This program creates a set structure as an unordered array. 
Sequential search is used to search for elements in an array and determine whether there are matching elements.

For Application 1 (unique.c), this program will read all distinct words in a given file and insert the distinct words in a set.
The total amount of unique words and the words themselves will be printed.

For Application 2 (parity.c), the set will maintain a collection of words that occur an odd number of times in a given file.
*/

#include <assert.h>
#include "set.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


//Set structure definition
struct set {
	int count;
	int length;
	char ** data;
};

/*Creates set and returns pointer to a new set with a max capacity of maxElts
Big-O notation: O(1)
 */
SET *createSet(int maxElts) {
	SET *sp;
	sp = (SET *)malloc(sizeof(SET));
	assert(sp != NULL);
	sp->count = 0;
	sp->length = maxElts;
	sp->data = (char **)malloc(sizeof(char*)*maxElts);
	assert(sp->data != NULL);
	return sp;
}

/*Static function, will be kept local to this file
Determines whether target element is in set
Big-O notation: O(n)
*/
static int search(SET *sp, char *elt) {
	assert(sp != NULL && elt != NULL);
	int i;
	for (i = 0; i < sp->count; i++) {
		int found = strcmp(sp->data[i], elt);
		//strcmp returns value of zero when strings are identical
		if (found == 0)
			return i; //i is the index at which the match is found
	}
	return -1; //no match found in set
}

/* Deallocates memory associated with the set pointed to by sp
 * Big-O notation: O(n)
 */
void destroySet(SET *sp) {
	int i;
	assert(sp != NULL);
	for (i = 0; i < sp->count; i++) {
		free(sp->data[i]);
	}
	free(sp->data);
	free (sp);
	return;
}

/*Returns the number of elements in the set pointed to by sp
Big-O notation: O(1) 
*/
int numElements(SET *sp) {
	assert(sp != NULL);
	return (sp->count);
}

/* Adds the element to the set pointed to by sp
 * Big-O notation: O(1)
 */
void addElement(SET *sp, char *elt) {
	assert(sp != NULL && elt != NULL);
	assert(sp->count < sp->length);

	//make sure not adding a duplicate elt
	if (search(sp, elt) != -1)
		return;
	
	//copyp is  a pointer which contains the location of the copy of elt
	char* copyp = strdup(elt);
	assert (copyp != NULL);	
	sp->data[sp->count] = copyp;
	(sp->count) ++;
	return;
}

/*Removes the element from the set pointed to by sp
 * Big-O notation: O(n)
 */
void removeElement(SET *sp, char*elt) {
	assert(sp != NULL && elt != NULL);
	int rm = search(sp, elt); //rm is the index at which the word will be removed
	if (rm == -1)
		return;
	free (sp->data[rm]);
	sp->data[rm] = sp->data[sp->count-1];	
	(sp->count)--;
	return;
}

/*Returns matching elt if present in set pointed to by sp
 * otherwise, returns NULL
 *Big-O notation: O(n)
 */
char *findElement(SET *sp, char *elt) {
	assert(sp != NULL && elt != NULL);
	int var = search(sp, elt);
	if (var != -1)
		return (sp->data[var]);
	return NULL;
}

/*allocates and returns array of elements in set pointed to by sp
Big-O notation: O(1) 
*/
char ** getElements(SET *sp) {
	assert(sp != NULL);
	char ** copy;
	copy = (char **)malloc(sizeof(char*)*sp->count);
	assert (copy != NULL);
	memcpy(copy, sp->data, sizeof(char*)*sp->count);
	return copy;
}
