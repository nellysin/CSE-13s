#include "code.h"
#include "defines.h"
#include "node.h"
#include "huffman.h"
#include "pq.h"

#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>

Node *build_tree(uint64_t hist [static ALPHABET]){ //CITE: TA Eugene & Tutor Eric
	Node *left; //create a new node for left
	Node *right; //create a new node for right
	Node *root; // the top priority with the most frequency

	//construct a histogram
	PriorityQueue *pq = pq_create(ALPHABET);
	for(int i = 0; i < ALPHABET; i += 1){
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

void build_codes(Node *root, Code table[static ALPHABET]){
	//walk the huffman tree to construct the corresponding code for each symbol
	Code c = {0, {0}};

	if(root->left == NULL && root->right == NULL){
		table[root->symbol] = c
	}		
	return;		
}
void dump_tree(int outfile, Node *root){
	return;
}

Node *rebuild_tree(uint16_t nbytes, uint8_t tree_dump[static nbytes]){
	return 0;
}

void delete_tree(Node **root){
	return;
}
