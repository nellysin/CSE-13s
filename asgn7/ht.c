#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "bst.h"
#include "ht.h"
#include "salts.h"
#include "speck.h"

uint64_t lookups = 0;

//CITE: Professor Long in Lecture slides 28
//CITE: TA Eugene for explaination on hashtables and given (11/24) section & statistics

struct HashTable { //struct for hash tables in asgn doc
    uint64_t salt[2];
    uint32_t size;
    Node **trees;
};

HashTable *ht_create(uint32_t size) { //create the hashtable
    HashTable *ht = (HashTable *) malloc(sizeof(HashTable));
    ht->size = size; //initialize the ht size
    ht->salt[0] = SALT_HASHTABLE_LO; //assign the ht to salts
    ht->salt[1] = SALT_HASHTABLE_HI;

    ht->trees = (Node **) calloc(size, sizeof(Node)); //we are creating the nodes of the trees
    if (!ht->trees) { //if it's not created then free
        free(ht);
        ht = NULL;
    }
    return ht; //returning the hashtables
}

void ht_delete(HashTable **ht) { //delete hash tables
    for (uint32_t i = 0; i < (*ht)->size; i += 1) {
        bst_delete(&(*ht)->trees[i]);
    }
    free((*ht)->trees); //freeing the nodes of the tree
    free(*ht); //free the hashtable
    *ht = NULL;
    return; //this is for no leakage memory
}

uint32_t ht_size(HashTable *ht) { //setting the size
    return ht->size;
}

Node *ht_lookup(HashTable *ht, char *oldspeak) {
    //searches for a node in the hashtable that contains oldspeak. The node stores oldspeak and its nespeak translation.
    //the index of the binary search tree to perform the "look-up" is by hashing the oldspeak
    //if the node is found, the pointer to the node is returned
    uint32_t index = hash(ht->salt, oldspeak) % ht_size(ht);
    lookups += 1; //this will be very important for statistics

    return bst_find(ht->trees[index], oldspeak);
}

void ht_insert(HashTable *ht, char *oldspeak, char *newspeak) {
    //inserts the specified oldspeak and its corresponding newspeak translation into the hash index of the binary search tree to insert
    //insert (index) is calculated by hashing the oldspeak
    uint32_t index = hash(ht->salt, oldspeak) % ht_size(ht);
    lookups += 1; //this will be very important for statistics

    ht->trees[index] = bst_insert(ht->trees[index], oldspeak, newspeak);
}
uint32_t ht_count(HashTable *ht) {
    //returning the number of not NULL binary search trees in the hashtable
    //we are using a for loop for this (count)
    uint32_t count = 0;
    for (uint32_t i = 0; i < ht->size; i += 1) {
        if (ht->trees[i]) {
            count += 1;
        }
    }
    return count;
}

double ht_avg_bst_size(HashTable *ht) {
    //returning the average binary search tree size.
    //We first must compute the sum of the sizes over binary search trees and divide the number of non-NULL bst in ht
    //by doing this we use the bst_size() function -- average is sum / total
    float total = 0;
    for (uint32_t i = 0; i < ht_size(ht); i += 1) {
        total += bst_size(ht->trees[i]);
    }
    return total / ht_count(ht);
}

double ht_avg_bst_height(HashTable *ht) {
    //similer to the avg_bst_size() we return the average binary search tree size. By doing this we comput the sum of the height with bst_height() and divide by the number of non-NULL bst in ht
    //double total;
    float to_divide = 0;
    for (uint32_t i = 0; i < ht_size(ht); i += 1) {
        to_divide += bst_height(ht->trees[i]);
    }
    return to_divide / ht_count(ht);
}
