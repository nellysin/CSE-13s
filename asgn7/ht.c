#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "bst.h"
#include "ht.h"
#include "salts.h"
#include "speck.h"

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
    if (bst_find(*ht->trees, oldspeak) != NULL) {
        return *ht->trees;
    } else {
        return false;
    }
}

void ht_insert(HashTable *ht, char *oldspeak, char *newspeak) {
    bst_insert(*ht->trees, oldspeak, newspeak);
}
uint32_t ht_count(HashTable *ht) {
    uint32_t count = 0;
    for (uint32_t i = 0; i < ht->size; i += 1) {
        if (ht->trees[i] != NULL) {
            count += 1;
        }
    }
    return count;
}

double ht_avg_bst_size(HashTable *ht) {
    return bst_size(*ht->trees) / ht_count(ht);
}
