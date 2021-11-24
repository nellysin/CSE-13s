#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "node.h"

//CITE: Professor Long for further explanation
//CITE: TA Eugene for assignment doc
//CITE: Tutor Jason for adding !oldspeak and !newspeak

Node *node_create(char *oldspeak, char *newspeak) {
    Node *n = (Node *) malloc(sizeof(Node)); //malloc for the node

    if (oldspeak != NULL) {
        n->oldspeak = strdup(oldspeak); //duplicate for oldspeak and newspeak is stored in the node
    }

    if (newspeak != NULL) {
        n->newspeak = strdup(newspeak);
    }

    n->left = NULL; //set left and right to null?
    n->right = NULL;

    return n;
}

void node_delete(Node **n) {
    free((*n)->oldspeak);
    free((*n)->newspeak);
    free(*n);
    *n = NULL;
}

void node_print(Node *n) {
    if (n->oldspeak != NULL && n->newspeak != NULL) {
        printf("%s -> %s\n", n->oldspeak, n->newspeak);
    }
    if (n->oldspeak != NULL) {
        printf("%s\n", n->oldspeak);
    }
}
