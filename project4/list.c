/*Mia Lassiter
 COEN 12
Project 4 Part 1: Deque

This is the implementation of a stack, using a deque
A dequeue is a doubly-ended queue ADT
The deque is implemented using a circular, doubly-linked list with a dummy node
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "set.h"
#include "list.h"
#include <stdbool.h>
#define LIST struct list
#define NODE struct node

//list definition
struct list {
    int count;
    struct node *head;
    int (*compare)();
};

//node definition
struct node {
    void *data;
    struct node *next;
    struct node *prev;
};

/* returns a pointer to a new list using compare as its comparison function, which may be NULL
Big-O notation: O(1)
*/
LIST *createList(int (*compare)()) {
	LIST *lp;
	lp = malloc(sizeof(LIST));
	assert (lp != NULL);
	lp->count = 0;
	lp->compare = compare;
	lp->head = malloc(sizeof (NODE));
	assert (lp->head != NULL);
	lp->head->next = lp->head;
	lp->head->prev = lp->head;
	lp->head->data = NULL;
	return lp;
}

/* deallocate memory associated with the list pointed to by lp
Big-O notation: O(n)
*/
void destroyList (LIST *lp) {
    assert(lp != NULL);
	NODE *pNext, *pDel;
	pDel = lp->head;
	//traverse list
	do {
		pNext = pDel->next;
		free(pDel);
		pDel = pNext;
	} while(pDel != lp->head);
	free(lp);
    return;
}

/* return the number of items in the list pointed to by lp
Big-O notation: O(1)
*/
int numItems(LIST *lp) {
    assert(lp != NULL);
    return lp->count;
}

/* add 'item' as the first item in the list pointed to by lp
Big-O notation: O(1)*/
void addFirst(LIST *lp, void *item) {
    assert (lp != NULL && item != NULL);
	NODE *newNode;
	newNode = (NODE *)malloc(sizeof(NODE));
	assert (newNode != NULL);
	newNode->data = item;
	newNode->next = lp->head->next;
	newNode->prev = lp->head;
	newNode->prev->next = newNode;
	newNode->next->prev = newNode;
	(lp->count)++;
    return;
}

/* add 'item' as the last item in the list pointed to by lp
Big-O notation: O(1)
*/
void addLast(LIST *lp, void *item) {
    assert (lp != NULL && item != NULL);
	NODE*newNode;
	newNode = (NODE *)malloc(sizeof(NODE));
	assert (newNode != NULL);
	newNode->data = item;
	newNode->next = lp->head;
	newNode->prev = lp->head->prev;
	newNode->next->prev = newNode;
	newNode->prev->next = newNode;
	(lp->count)++;
    return;
}

/*remove and return the first item in the list pointed to by lp
the list must not be empty
Big-O notation: O(1)
*/
void *removeFirst(LIST *lp) {
	assert (lp != NULL);
	NODE *pDel = lp->head->next;
	void *cpData = pDel->data;
	lp->head->next = pDel->next;
	pDel->next->prev = lp->head;
	free (pDel);
	lp->count--;
	return cpData;
}

/*remove and return the last item in the list pointed to by lp
the list must not be empty
Big-O notation: O(1)
*/
void *removeLast(LIST *lp) {
	assert (lp != NULL);
	NODE *pDel = lp->head->prev;
	void *cpData = pDel->data;
	lp->head->prev = pDel->prev;
	pDel->prev->next = lp->head;
	free (pDel);
	lp->count--;
	return cpData;
}

// return, but do not remove, the first item in the list pointed to by lp
//the list must not be empty
//Big-O notation: O(1)

void *getFirst(LIST *lp) {
    assert (lp != NULL);
    return lp->head->next->data;
}

// return, but do not remove, the last item in the list pointed to by lp
//the list must not be empty
//Big-O notation: O(1)

void *getLast(LIST *lp) {
    assert (lp != NULL);
    return lp->head->prev->data;
}

/* if 'item' is present in the list pointed to by lp, then remove it
//the comparison function must not be NULL
//Big-O notation: O(n)
*/
void removeItem(LIST *lp, void *item) {
    assert (lp != NULL && item != NULL);
	NODE *ptr;
	ptr = lp->head->next;//ptr is a pointer to the first element in the list
	while (ptr != lp->head) {
		if ((*lp->compare)(ptr->data,item) == 0) {
			//reassign prev and next pointers
			ptr->prev->next = ptr->next;
			ptr->next->prev = ptr->prev;
			free(ptr);
			(lp->count)--;
			return;
		}
		ptr = ptr->next;
	}//end while
    return;
}

/* if 'item' is present in the list pointed to by lp, then return the matching item
//otherwise, return NULL
//the comparison function must not be NULL
//Big-O notation: O(n)
*/
void *findItem(LIST *lp, void *item) {
    assert (lp != NULL && item != NULL);
	NODE *ptr;
	ptr = lp->head->next;//ptr is a pointer to the first element in the list
	while (ptr != lp->head) {
		if ((*lp->compare)(ptr->data,item) == 0) 
			return (ptr->data);
		ptr = ptr->next;
	}//end while
    return NULL;
}

// allocate and return an array of items in the list pointed to by lp
//Big-O notation: O(n)

void *getItems(LIST *lp) {
    assert (lp != NULL);
	void **itemArray = malloc(sizeof(void *) * lp->count);
	assert(itemArray != NULL);
	int i = 0;
	NODE *ptr = lp->head->next;
	for (i = 0; i < lp->count; i++) {
		itemArray[i] = ptr->data;
		ptr = ptr->next;
	}			
    return itemArray;
}
