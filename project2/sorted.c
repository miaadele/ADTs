/*Mia Lassiter
COEN 12 
Project 2: Sorted set

This program creates a set structure as an ordered array. 
Binary search is used to search for elements in an array and determine whether there are matching elements.

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
Big-O notation: O(log(n))
*/
static int search(SET *sp, char *elt, bool *found) {
	assert(sp != NULL && elt != NULL && found!=NULL);
	int lo = 0, mid, hi = (sp->count)-1;
	while (lo <= hi) { 
		mid = (hi + lo) / 2;
		if (strcmp(elt, sp->data[mid]) == 0) {
			*found = true;
			return mid;//returns index at which matching data is found, where elt will be added
		}
		else if (strcmp(elt, sp->data[mid]) > 0) 
			//first nonmatching character of elt has a greater ASCII value than the corresponding char pointed to by sp
			lo = mid + 1;
		else
			//first nonmatching character of elt has a lesser ASCII value than the corresponding char pointed to by sp
			hi = mid - 1;
	} //end while
	*found = false;
	return lo; 
}

/* Deallocates memory associated with the set pointed to by sp
 * Big-O notation: O(n)
 */
void destroySet(SET *sp) {
	int i;
	assert(sp != NULL);
	for (i = 0; i < sp->count; i++)
		free(sp->data[i]);
	free(sp->data);
	free (sp);
	return;
}

/*Returns the number of elements in the set pointed to by sp
 * Big-O notation: O(1)
 */
int numElements(SET *sp) {
	assert(sp != NULL);
	return (sp->count);
}

/* Adds the element to the set pointed to by sp
 * Big-O notation: O(log(n)) 
 */
void addElement(SET *sp, char *elt) {
	assert(sp != NULL && elt != NULL);
	assert(sp->count < sp->length);
	bool found;
	
	//make sure not adding a duplicate elt
	int ind = search(sp, elt, &found);
	if (found == true)
		return;
	
	//shift all elements down one index, start at the end of the data
	int i;
	for (i = sp->count; i > ind; i--)
		sp->data[i] = sp->data[i-1];
	//sp->data[i] is now empty. This is where elt will be inserted
	
	//copyp is  a pointer which contains the location of the copy of elt
	char* copyp = strdup(elt);
	assert(copyp != NULL);	
	sp->data[ind] = copyp;
	(sp->count) ++;
	return;
}

/*Removes the element from the set pointed to by sp
 * Shifts all elements to close the gap
 * Big-O notation: O(n)
 */
void removeElement(SET *sp, char*elt) {
	bool found;
	assert(sp != NULL && elt != NULL);

	int ind = search(sp, elt, &found);
	if (found == false)
		return;

	int i;
	free(sp->data[ind]);
	//shift all elements up one index
	for (i = ind; i < sp->count-1; i++)
		sp->data[i] = sp->data[i+1];
	(sp->count)--;
	return;
}

/*Returns matching elt if present in set pointed to by sp
 * otherwise, returns NULL
 *Big-O notation: O(log(n))
 */
char *findElement(SET *sp, char *elt) {
	bool found;
	assert(sp != NULL && elt != NULL);
	int i = search(sp, elt, &found);

	//Ternary operator, more efficient way of coding an if-else statement
	return found ? sp->data[i] : NULL;
}

/*allocates and returns array of elements in set pointed to by sp
 *Big-O notation: O(1)
 */
char ** getElements(SET *sp) {
	assert(sp != NULL);
	char ** copy;
	
	copy = (char **)malloc(sizeof(char*)*sp->count);
	assert (copy != NULL);
	memcpy(copy, sp->data, sizeof(char*)*sp->count);
	return copy;
}
