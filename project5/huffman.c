/* Mia Lassiter
 * COEN 12L Lab5 Part 2: Huffman Coding
 This program compresses the input text file into an output file with ".z" extension
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include "pack.h"
#include "pqueue.h"
#include <stdbool.h>
typedef struct node NODE;

//Private function: make node
//Big-O notation: O(1)
static NODE *mknode(int count, NODE* left_node, NODE *right_node){
	struct node *new_node;
	new_node = malloc(sizeof(struct node));
	assert(new_node != NULL);
	new_node->count = count; //sum of the two children
	new_node->parent = NULL;
	//if (left_node->parent != NULL)
	if (left_node != NULL)
		left_node->parent = new_node;
	//wif (right_node->parent != NULL)
	if (right_node != NULL)
		right_node->parent = new_node;
	return new_node;
}

/*Comparison function for createQueue
compares tree1->count with tree2->count
Big-O notation: O(1)
*/
int compare(NODE *tree1, NODE *tree2) {
	if (tree1->count < tree2->count)
		return -1;
	else if (tree1->count > tree2->count)
		return 1;
	else
		return 0;
}

/*calculate the number of bits per char
Big-O notation: O(1) */
static int depth(NODE *node) {
	int numBits = 0;
	while (node->parent != NULL) {
		numBits++;
		node = node->parent;
	}
	return numBits;
}

//Big-O notation: O(n)
int main (int argc, char *argv[]) {
	FILE *fptr;  //pointer for input.txt
	fptr = fopen(argv[1], "r");
	if (fptr == NULL ) //unable to open file
		return -1;

	/*int array to store the frequencies for the characters
	each index represents a letter
	initialize each frequency to 0 */
	int counts[257] = {0};

	/*initialize each node to point to NULL
	each index represents a letter */
	NODE *nodes[257] = {NULL};

	//initialize an array for a priority queue
	PQ *pq = createQueue(compare);	

	//count the number of occurences of each char in the file
	int i, c;
	do {
		c = getc(fptr);
		counts[c]++;
	} while (c != EOF);
	//traverse counts array
	
	for (i = 0; i < 257; i++) {
		if(counts[i] != 0) {
			nodes[i] = mknode(counts[i], NULL, NULL); //makes leaf node
			addEntry(pq, nodes[i]);
		}
	}
	nodes[256] = mknode(counts[256], NULL, NULL); //node for EOF
	addEntry(pq, nodes[256]);

	//build tree
	while (numEntries(pq) > 1) {
		//remove the two lowest priority trees
		NODE *tree1 = removeEntry(pq);
		NODE *tree2 = removeEntry(pq);
		//make a new tree and insert it into the priority queue	
		NODE *new_node = mknode( tree1->count + tree2->count, tree1, tree2);
		addEntry(pq, new_node);	
	} //end while
	
	for (i = 0; i < 257; i++ ) {
		if (counts[i] != 0 || i == 256) {
			if (isprint(i) == 0) //char is not printable
				printf("%03o ", i);
			else
				printf("'%c' ", i);

			printf("- %d x %d bits = %d bits\n", 
			counts[i], depth(nodes[i]), counts[i]*depth(nodes[i]));
		}
	}
	//generate the compressed file	
	pack(argv[1], argv[2], nodes);
	fclose (fptr);
	return 0;
}
