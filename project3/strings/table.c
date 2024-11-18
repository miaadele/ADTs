/*Mia Lassiter
COEN 12 
Project 3 Part 1: Hash Table

This program creates a hash table 

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

//Flag defines
#define EMPTY 0
#define FILLED 1
#define DELETED 2

//Set structure definition
struct set {
	int count;
	int length;
	char ** data;
	char *flags;
};

/*Creates set and returns pointer to a new set with a max capacity of maxElts
Big-O notation: O(n)
 */
SET *createSet(int maxElts) {
	SET *sp;
	sp = (SET *)malloc(sizeof(SET));
	assert(sp != NULL);
	sp->count = 0;
	sp->length = maxElts;
	sp->data = (char **)malloc(sizeof(char*)*maxElts);
	sp->flags = (char *)malloc(sizeof(char*)*maxElts);
	assert((sp->data != NULL) && (sp->flags != NULL));
	int i;
	//initialize all flags to empty
	for (i = 0; i < sp->length; i++)
		sp->flags[i] = EMPTY;
	return sp;
}

/*Creates hash table
 * Big-O notation: O(n)
 */
static unsigned strhash(char *s) {
	unsigned hash = 0;
	while (*s != '\0')
		hash = 31 * hash + *s++;
	return hash;
}

/*Static function, will be kept local to this file
Determines whether target element is in set
Big-O notation: O(n) 
*/
static int search(SET *sp, char *elt, bool *found) {
	assert(sp != NULL && elt != NULL && found != NULL);
	int locn = (strhash(elt))%sp->length;
	int i;
	int delt_locn = -1;
	*found = false;
	//loop through array
	for (i = 0; i < sp->length; i++) {
		int x = (locn + i)%sp->length;
		if (sp->flags[x] == FILLED) {
			int match = strcmp(sp->data[x], elt);
			if (match == 0){
				*found = true;
				return x;
			}
		}//end if 
		else if (sp->flags[x] == DELETED) {
			//record the index number of the first deleted spot
			if (delt_locn == -1)
				delt_locn = x;
		} 
		else {
			if (delt_locn == -1)
				return x;
			else
				return delt_locn;
		}
	} //end for
	return delt_locn;
}

/* Deallocates memory associated with the set pointed to by sp
 * Big-O notation: O(n)
 */
void destroySet(SET *sp) {
	int i;
	assert(sp != NULL);
	for (i = 0; i < sp->length; i++)
		if (sp->flags[i] == FILLED)
			free(sp->data[i]);
	free(sp->data);
	free(sp->flags);
	free(sp);
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
 * Big-O notation: O(n)
 */
void addElement(SET *sp, char *elt) {
	assert(sp != NULL && elt != NULL);
	assert(sp->count < sp->length);
	bool found;

	//make sure not adding a duplicate elt
	int x = search(sp, elt, &found);
	if (found != true){	
		//copyp is  a pointer which contains the location of the copy of elt
		char* copyp = strdup(elt);
		assert (copyp != NULL);	
		sp->data[x] = copyp;
		sp->flags[x] = FILLED;
		(sp->count) ++;
	}
	return;
}

/*Removes the element from the set pointed to by sp
 * Big-O notation: O(n)
 */
void removeElement(SET *sp, char*elt) {
	bool found;
	assert(sp != NULL && elt != NULL);
	int rm = search(sp, elt, &found); //rm is the index at which the word will be removed
	if (found == true){
		free (sp->data[rm]);
		sp->flags[rm] = DELETED;
		(sp->count)--;
	}
	return;
}

/*Returns matching elt if present in set pointed to by sp
 * otherwise, returns NULL
 *Big-O notation: O(n)
 */
char *findElement(SET *sp, char *elt) {
	assert(sp != NULL && elt != NULL);
	bool found;
	int var = search(sp, elt, &found);
	if (found == true)
		return (sp->data[var]);
	return NULL;
}

/*allocates and returns array of elements in set pointed to by sp
Big-O notation: O(n)
*/
char ** getElements(SET *sp) {
	assert(sp != NULL);
	char **copy;
	copy = malloc(sizeof(char*)*sp->count);
	assert (copy != NULL);
	int i;
	int copyIndex = 0;
	for (i = 0; i < sp->length; i++) {
		if (sp->flags[i] == FILLED){
			copy[copyIndex] = sp->data[i];	
			assert(copy[copyIndex] != NULL);
			copyIndex++;
		}
	}//end for
	return copy;
}
