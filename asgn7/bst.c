#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "node.h"
#include "bst.h"

//CITE: Professor Long for code in the lecture slide 18

Node *bst_create(void){
	Node *root;
	Node *node_create(NULL, NULL);
	return root;
}

uint32_t bst_height(Node *root){
	uint32_t bst_left = bst_height(root->left);
	uint32_t bst_right =  bst_height(root->right);
	if(root){
		return 1 + bst_left > bst_right ? bst_left : best_right;
	}
	return 0;
}

uint32_t bst_size(Node *root);

Node *bst_find(Node *root, char *oldspeak){
	if(root){
		if(root->oldspeak > oldspeak){
			return bst_find(root->left, oldspeak);
		} else if (root->oldspeak < oldspeak){
			return bst_find(root->right, oldspeak);
		}
	}
	return root;
}

Node *bst_insert(Node *root, char *oldspeak, char *newspeak);//{
	/*if(root){
		if(root->oldspeak > oldspeak){
			root->left = bst_insert(root->left, oldspeak);
		} else {
			root->right = bst_insert(root->right, oldspeak);
		}
		if(root->newspeak > newspeak){
			root->left = bst_insert(root->left, newspeak);
		} else {
			root->right = bst_insert(root->right, newspeak);
		}
		return root;
	}
	return node_create()*/
//}

void bst_print(Node *root);

void bst_delete(Node **root){
	if(*root){
		bst_delete(&(*root)->left);
		bst_delete(&(*root)->right);
		node_delete(root);
	}
}
