#include "code.h"
#include "defines.h"
#include "node.h"
#include "huffman.h"
#include "pq.h"
#include "io.h"
#include "stack.h"

#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>

Node *build_tree(uint64_t hist [static ALPHABET]){ //CITE: TA Eugene 10/26 section & Tutor Eric 11/3 sessioin for build tree sudo code
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

//this is to traverse the huffman tree in build codes, separate function to take in Code c (helper function to make my code a little cleaner and understandable)
/*void traverse_code(Node *root, Code table[static ALPHABET], Code c){ 
	//CITE: TA Eugene 10/26 section for build_codes for TRAVERSE_CODE
	//CITE: Professor Long for pseudocode in assignment doc
	//This is similar to DFS
        //We want to represent freq occuring symbols w/ fewer bits
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
}*/

static Code c;
void build_codes(Node *root, Code table[static ALPHABET]){ 
	//CITE: TA Eugene 10/26 section & Tutor Eric 11/3 session four BUILD_CODES
	//CITE: Professor Long for pseudocode in assgment doc
	//walk the huffman tree to construct the corresponding code for each symbol
	c = code_init(); //initialize code c
	uint8_t i; //a variable to where the bit is popped
        if(root->left == NULL && root->right == NULL){ //letters can only be leaf nodes!!
                table[root->symbol] = c;
        } else {
                if(root->left != NULL){ //everytime we go to the left tree
                        code_push_bit(&c, 0); //we add a 0 to the code stack
                        build_codes(root->left, table); //each symbol will have one code 
                        code_pop_bit(&c, &i); //going back up -- pop the last bit
                }
                if(root->right != NULL){ //everytime we go to the right path
                        code_push_bit(&c, 1); //we push a 1
                        build_codes(root->right, table); //each symbol will have one code
                        code_pop_bit(&c, &i); //going back up -- pop the last bit
                }
        }
	return;		
}

void dump_tree(int outfile, Node *root){ 
	//CITE: TA Eugene 10/26 section, 11/4 section & Tutor Jason on 11/4 (buffer)
	//CITE: Professor Long for pseudocode in assignment doc
	//post order traversal -- dumping the tree (going as far as we can in the tree)
	//static uint8_t tree_buffer[] = {'L', 'I'}; //using a static buffer for the symbol as well

	uint8_t leaf = 'L'; //leaf for 'L'
	uint8_t interior = 'I'; //interior is 'I'

	//post order(n)
	//if node isn't null
	if(root != NULL){
		dump_tree(outfile, root->left); //post order (n->left)
		dump_tree(outfile, root->right); //post order(n->right) 
		//if root->left or root->right is a leaf
		if(root->left == NULL && root->right == NULL){
		//	tree_buffer[0] = 'L'; //setting to 'L'
			write_bytes(outfile, &leaf, 1); //when on a leaf node "L" followed by the symbol of node "c"
			write_bytes(outfile, &root->symbol, 1);
		} else { //if this is not a interior 
		//	tree_buffer[1] = 'I'; //setting the 'I'
			write_bytes(outfile, &interior, 1); //if it is an interior node "I" followed by the symbol of the node
		}
	}
	return;
}

Node *rebuild_tree(uint16_t nbytes, uint8_t tree[static nbytes]){ //CITE: TA Eugene for rebuild tree sudo in 11/4 section
	Stack *s = stack_create(nbytes); //we must create a stack for the parents
	//loop for dumping
	for(uint32_t i = 0; i < nbytes; i += 1){ //if we dump 'L'
		if(tree[i] == 'L'){
			uint32_t next = i + 1; //for the next 
			Node *n = node_create(tree[next], 0); //that means the next index will be a symbol
			stack_push(s, n); //push the node to the stack
		}
		//when we reach the parent node
		if(tree[i] == 'I'){ //if we dump 'I'
			Node *right; //initiliaze right
			Node *left; //initialize left
			stack_pop(s, &right); //pop the right 
			stack_pop(s, &left); //pop the left
			Node *n = node_join(left, right); // the parent is n and will be using node join for left and right
			stack_push(s, n); //push the parent to the stack
		}
	}
	// we have to return the root 
	Node *root; //node for root
	stack_pop(s, &root); //pop the top of the stack to the root 
	stack_delete(&s);  //and delete the the top of the stack after
	return root;
}

void delete_tree(Node **root){ //CITE: TA Eugene for pseudo of delete tree
	//need to do postorder traversal
	if(*root){
		if((*root)->left != NULL){ //traversing back
			delete_tree(&(*root)->left);
		}
		if((*root)->right != NULL){ //traversing back
			delete_tree(&(*root)->right);
		}
		node_delete(root); //deleting the root
	}
	return;
}
