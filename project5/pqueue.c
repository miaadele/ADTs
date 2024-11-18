/*Mia Lassiter
COEN 12 Lab 5 Part 1: Priority Queue
This code implements a priority queue ADT through a binary heap
The binary heap is implemented using an array
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "pqueue.h"

//global definitions of parent, left child, and right child
#define p(x) (((x)-1)/2)
#define lc(x) ((x)*2 + 1)
#define rc(x) ((x)*2 +2)

//structure definition
struct pqueue {
	int count; //number of entries in array
	int length; //length of allocated array
	void **data; //allocated array of entries
	int (*compare)();
};

/*Return a pointer to a new priority queue using 'compare' as its comparison function
Big-O notation: O(1)
 */
PQ *createQueue(int(*compare)()) {
	PQ *pq;
	pq = malloc(sizeof(PQ));
	assert (pq != NULL);
	//initialize structure members
	pq->count = 0;
	pq->length = 10;
	pq->data = malloc(sizeof(void *)*pq->length);
	pq->compare = compare;	
	return pq;	
}

/*Deallocate memory associated with the priority queue pointed to by pq
Big-O notation: O(1)
 */
void destroyQueue(PQ *pq){
	free (pq);
	return;
}

/*Return the number of entries in the priority queue pointed to by pq
Big-O notation: O(1)
 */
int numEntries(PQ *pq){
	assert(pq != NULL);
	return pq->count;
}

/*Add 'entry' to the priority queue pointed to by pq
Assume 'entry' starts at the end and reheap up,move data in child up to its current location in the heap array
Big-O notation: O(log n)
*/
void addEntry(PQ *pq, void *entry){
	//check whether heap is full
	if (pq->count == pq->length) {
		//double the size of the array
		pq->data = realloc(pq->data, sizeof(void *)* 2*(pq->length));
		assert (pq->data != NULL);
	}	
	int x = pq->count; //x is the index of the first empty spot
	while (x > 0) { //while the tree is not empty
		if ((*pq->compare)(entry, pq->data[p(x)]) < 0) {
			//if entry < parent, move parent to location x
			pq->data[x] = pq->data[p(x)];
			x = p(x);
		}
		else
			break;
	} //end while
	pq->data[x] = entry;
	pq->count++;
	return;	
}

/*Remove and return the smallest entry from the priority queue pointed to by pq
Save the root and replace it with the element at the end, then reheap down
Big-O notation: O(log n)
*/
void *removeEntry(PQ *pq){
	//store smallest entry in temp variable
	void *del = pq->data[0];
	int x = pq->count-1;
	int smaller;
	//move last element to top of heap
	pq->data[0] = pq->data[x];
	(pq->count)--;

	x = 0;  //start at root
	while (lc(x) <= pq->count-1){  //while the lc exists
		smaller = lc(x);
		if (rc(x) <= pq->count-1){  //if rc exists
			//compare lc and rc
			if ((*pq->compare)(pq->data[lc(x)], pq->data[rc(x)]) > 0) 
				//if left is greater than right
				smaller = rc(x);
		} //end if
		
		if ((*pq->compare)(pq->data[x], pq->data[smaller]) > 0) {
			//swap root and pq->data[smaller]
			void* temp = pq->data[x];
			pq->data[x] = pq->data[smaller];
			pq->data[smaller] = temp;
			x = smaller;
		}
		else {
			break;
		}
	} //end while 
	return del;	
}
