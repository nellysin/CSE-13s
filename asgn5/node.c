#include "node.h"

#include <stdint.h>
#include <stdlib.h>

//CITE: Professor Long for sudo code
//CITE: TA Eugene for structure

Node *node_create(uint8_t symbol, uint64_t frequency) {
    Node *n = (Node *) malloc(sizeof(Node)); //initalizing the calloc
    n->symbol = symbol; //initiliazing the symbol and frequency in node
    n->frequency = frequency;
    n->left = NULL;
    n->right = NULL;
    return n;
}

void node_delete(Node **n) {
    free(*n); // delete the node after you're done
    *n = NULL;
    return;
}

Node *node_join(Node *left, Node *right) {
    Node *parent = node_create(
        '$', left->frequency + right->frequency); //creating the parent node from node create
    parent->left = left; //initializing left and right
    parent->right = right;
    return parent; //returning parent
}
