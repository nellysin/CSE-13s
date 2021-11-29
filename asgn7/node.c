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
        n->oldspeak = strdup(oldspeak); //duplicate the oldspeak and store in the n->oldspeak
    } else {
        n->oldspeak = NULL; //if oldspeak does not exist
    }

    if (newspeak != NULL) {
        n->newspeak = strdup(newspeak); //duplicate the newspeak and stored in the n->newspeak
    } else {
        n->newspeak = NULL; //if newspeak does not exist
    }

    n->left = NULL; //set left and right to null?
    n->right = NULL;

    return n;
}

//this is to free a node for if the oldspeak is not NULL
void node_delete(Node **n) {
    if (*n) { //if n exists
        if ((*n)->oldspeak) { //n->oldspeak exists then free the oldspeak
            free((*n)->oldspeak);
        }
        if ((*n)->newspeak) { //n->newspeak exists then free the newspeak
            free((*n)->newspeak);
        }
        free(*n); //free node
        *n = NULL; //set the node to NULL
    }
}

//printing the nodes for what words are in badspeak or newspeak -- this must be used for the end of program
void node_print(Node *n) {
    if (n->oldspeak != NULL && n->newspeak != NULL) { //if the oldspeak and newspeak is not null
        printf("%s -> %s\n", n->oldspeak, n->newspeak); //print the oldspeak and newspeak
    }
    if (n->oldspeak != NULL && n->newspeak == NULL) { //if oldspeak is not null and newspeak is null
        printf("%s\n", n->oldspeak); //print only the oldspeak
    }
}
