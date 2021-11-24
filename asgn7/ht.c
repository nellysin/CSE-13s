#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "bst.h"
#include "ht.h"
#include "salts.h"
#include "speck.h"

//CITE: Professor Long in Lecture slides 28

struct HashTable {
    uint64_t salt[2];
    uint32_t size;
    Node **trees;
};

HashTable *ht_create(uint32_t size) {
    HashTable *ht = (HashTable *) malloc(sizeof(HashTable));
    ht->size = size;
    ht->salt[0] = SALT_HASHTABLE_LO;
    ht->salt[1] = SALT_HASHTABLE_HI;

    ht->trees = (Node **) calloc(size, sizeof(Node));
    if (!ht->trees) {
        free(ht);
        ht = NULL;
    }
    return ht;
}

void ht_delete(HashTable **ht) {
    if (*ht && (*ht)->trees) {
        free((*ht)->trees);
        free(*ht);
        *ht = NULL;
    }
    return;
}

uint32_t ht_size(HashTable *ht) {
    return ht->size;
}

Node *ht_lookup(HashTable *ht, char *oldspeak) {
	uint32_t index = hash(ht->salt, oldspeak) % ht_size(ht);

	return bst_find(ht->trees[index], oldspeak);
}

void ht_insert(HashTable *ht, char *oldspeak, char *newspeak) {
    uint32_t index = hash(ht->salt, oldspeak) % ht_size(ht);

    ht->trees[index] = bst_insert(ht->trees[index], oldspeak, newspeak);
}
uint32_t ht_count(HashTable *ht) {
    uint32_t count = 0;
    for (uint32_t i = 0; i < ht->size; i += 1) {
        if (ht->trees[i]) {
            count += 1;
        }
    }
    return count;
}

double ht_avg_bst_size(HashTable *ht) {
    uint32_t total = 0;
    for(uint32_t i = 0; i < ht_size(ht); i += 1){
	total += bst_size(ht->trees[i]);
    }
    double average;
    return average = total / ht_count(ht);

}

double ht_avg_bst_height(HashTable *ht){
	double total;
	uint32_t to_divide = 0;
	for(uint32_t i = 0; i < ht_size(ht); i += 1){
		to_divide += bst_height(ht->trees[i]);
	}
	return total = to_divide / ht_count(ht);
}	
