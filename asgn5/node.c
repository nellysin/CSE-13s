#include "node.h"

#include <stdint.h>
#include <stdlib.h>

Node *node_create(uint8_t symbol, uint64_t frequency){
	Node *n = (Node *)calloc(1, sizeof(Node));
	n->symbol = symbol;
	n->frequency = frequency;
	return n;
}

void node_delete(Node **n){
	free(n);
	n = NULL;
	return;
}

Node *node_join(Node *left, Node *right){
	parent->frequency = left->frequency + right->frequency;
	Node *parent = node_create('$', parent->frequency);
	return parent;
}
