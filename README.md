Projects from the course "Abstract Data Types and Structures"
For each, the interface and implementation are kept separate.

Project 2: set ADT for strings
Implementation: 
1) implement a set using an unsorted array of length m>0, in which the first n ≤ m slots are used to hold n strings in some arbitrary order. Use sequential search to locate an element in the array.
2) implement a set using a sorted array of length m > 0, in which the first n ≤ m slots are used to hold n strings in ascending order. Use binary search to locate an element in teh array.

Project 3: sets, arrays, and hash tables
1) Implement a set using a hash table of length m > 0 and linear probing to resolve collisions.
2) Implement a generic set ADT (a set that uses generic pointer types instead of strings).

Project 4: hashing with chaining
1) circular, doubly-linked list with a sentinel node.
   - use a stack to generate and solve a maze. The stack keeps track of the path so if the robot reaches a dead end, it can backtrack and explore alternative paths.
   - radix sort: program reads in a sequence of non-negative integers from the standard input and then writes them in sorted order on the standard output.
2) hash table with chaining for collision resolution
   - if at most n keys will be inserted, you should create m = dn/αe lists, where α is a constant with a value of 20. Assuming uniform hashing, then each list will contain n/m = α elements and the expected search time will be (α + 1)/2.
  
Project 5: priority queue ADT using a binary heap implemented using an array
1) heapsort
2) Huffman coding: a variable-length coding technique that can be used for lossless data compression. The program requires two filenames as command-line arguments.
   - The first filename is the file to be compressed, and the second filename is the file to hold the compressed data.
   - This program constructs the Huffman tree for the first file and displays the total number of occurrences and length of the Huffman code for each character to the standard output. 
