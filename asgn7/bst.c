#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "node.h"
#include "bst.h"

uint64_t branches = 0; //this is for statistics

//CITE: Professor Long for code in the lecture slide 18
//CITE: TA Eugene for statistics instructions

//this is our constructor for a binary search tree that constructs an empty tree (NULL)
Node *bst_create(void) {
    Node *root = NULL;
    return root;
}

//Helper function (given by professor long lecture slides 18)
//if x > y then set to x otherwise set to y
static int max(int x, int y) {
    return x > y ? x : y;
}

//returning the hight of the binary search tree rooted at the root
uint32_t bst_height(Node *root) {
    if (root) {
        return 1 + max(bst_height(root->left), bst_height(root->right));
    }
    return 0;
}

//this will be returning the size of the binary search tree rooted at the root. But the size of the tree equals to the number of nodes in the tree
uint32_t bst_size(Node *root) {
    int size = 0;
    if (root == NULL) {
        return 0;
    } else {
        size = 1 + bst_size(root->left) + bst_size(root->right);
    }
    return size;
}

//We must search for a node that contains the oldspeak in the binary search tree rooted at root.
//if the node is found and the pointer to the node is returned. Otherwise the pointer will be returned as NULL
Node *bst_find(Node *root, char *oldspeak) {
    if (root) {
        if (strcmp(root->oldspeak, oldspeak) > 0) {
            branches += 1; //this is for statistics
            return bst_find(root->left, oldspeak);
        } else if (strcmp(root->oldspeak, oldspeak) < 0) {
            branches += 1; //this is for statistics
            return bst_find(root->right, oldspeak);
        }
    }
    return root;
}

//In this function, it will insert a new node containing the specified oldspeak and newspeak into the binary search tree rooted at root. *!!BUT DUPLICATES shoulds not be inserted!!*
Node *bst_insert(Node *root, char *oldspeak, char *newspeak) {
    if (root) {
        if (strcmp(root->oldspeak, oldspeak) > 0) {
            branches += 1; //this is for statistics
            root->left = bst_insert(root->left, oldspeak, newspeak);
        } else if (strcmp(root->oldspeak, oldspeak) < 0) {
            branches += 1; //this is for statistics
            root->right = bst_insert(root->right, oldspeak, newspeak);
        }
        return root;
    }
    return node_create(oldspeak, newspeak);
}

//By using bst print, it will print out each node in the binary search tree through an inorder traversal. This will be similar to node_print()
void bst_print(Node *root) {
    if (root) {
        bst_print(root->left);
        node_print(root);
        bst_print(root->right);
    }
}

//we must free and delete for no memory leakage
void bst_delete(Node **root) {
    if (*root) {
        if ((*root)->left) {

            bst_delete(&(*root)->left);
        }
        if ((*root)->right) {
            bst_delete(&(*root)->right);
        }
        node_delete(root);
    }
}
