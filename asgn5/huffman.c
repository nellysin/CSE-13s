#include "code.h"
#include "defines.h"
#include "node.h"
#include "huffman.h"
#include "pq.h"

#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>

Node *build_tree(uint64_t hist [static ALPHABET]){ //CITE: TA Eugene 10/26 section & Tutor Eric 11/3 session
	Node *left; //create a new node for left
	Node *right; //create a new node for right
	Node *root; // the top priority with the most frequency

	//construct a histogram
	PriorityQueue *pq = pq_create(ALPHABET); //we are trying min heap (pq)
	for(int i = 0; i < ALPHABET; i += 1){ //min heap = every parent node <= the value of the children
		if(hist[i] > 0){
			Node *parent = node_create(i, hist[i]); 
			enqueue(pq, parent);
		}
	}	

	//perform prioriority qeue
	while(pq_size(pq) > 1){
		dequeue(pq, &left);
		dequeue(pq, &right);
		enqueue(pq, node_join(left, right));
	}
	//root = dequeue
	dequeue(pq, &root);
	pq_delete(&pq);
	return root;
	
}

//this is to traverse the huffman tree in build codes, separate function to take in Code c
void traverse_code(Node *root, Code table[static ALPHABET], Code c){ //CITE: TA Eugene 10/26 section for build_codes sudo
	//This is similar to DFS
        //We want to represent freq occuring symbols w/ fewer bits
        //CITE: Professor Long in comments repo in amazeme
	uint8_t i; //a variable to where the bit is popped
	if(root->left == NULL && root->right == NULL){ //letters can only be leaf nodes!!
                table[root->symbol] = c;
        } else {
                if(root->left != NULL){ //everytime we go to the left tree
                        code_push_bit(&c, 0); //we add a 0 to the code stack
                        traverse_code(root->left, table, c); //each symbol will have one code 
                        code_pop_bit(&c, &i); //going back up -- pop the last bit
                }
                if(root->right != NULL){ //everytime we go to the right path
                        code_push_bit(&c, 1); //we push a 1
                        traverse_code(root->right, table, c); //each symbol will have one code
                        code_pop_bit(&c, &i); //going back up -- pop the last bit
                }
        }
        return;
}

void build_codes(Node *root, Code table[static ALPHABET]){ //CITE: TA Eugene 10/26 section & Tutor Eric 11/3 session
	//walk the huffman tree to construct the corresponding code for each symbol
	Code c = code_init(); // initialize c in code
	traverse_code(root, table, c); //call the traverse order
	return;		
}
//void dump_tree(int outfile, Node *root){
//	return;
//}

//Node *rebuild_tree(uint16_t nbytes, uint8_t tree_dump[static nbytes]){
//	return 0;
//}

//void delete_tree(Node **root){
//	return;
//}
