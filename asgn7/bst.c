#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "node.h"
#include "bst.h"

//CITE: Professor Long for code in the lecture slide 18

Node *bst_create(void) {
    Node *root = node_create(NULL, NULL);
    root = NULL;
    return root;
}

static int max(int x, int y) {
    return x > y ? x : y;
}

uint32_t bst_height(Node *root) {
    if (root) {
        return 1 + max(bst_height(root->left), bst_height(root->right));
    }
    return 0;
}

uint32_t bst_size(Node *root) {
    int size = 0;
    if (root == NULL) {
        return false;
    } else {
        size = 1 + bst_size(root->left) + bst_size(root->right);
    }
    return size;
}

Node *bst_find(Node *root, char *oldspeak) {
    if (root) {
        if (strcmp(root->oldspeak, oldspeak) > 0) {
            return bst_find(root->left, oldspeak);
        } else if (strcmp(root->oldspeak, oldspeak) < 0) {
            return bst_find(root->right, oldspeak);
        }
    }
    return root;
}

Node *bst_insert(Node *root, char *oldspeak, char *newspeak) {
    if (root) {
        if (strcmp(root->oldspeak, oldspeak) > 0) {
            root->left = bst_insert(root->left, oldspeak, newspeak);
        } else {
            root->right = bst_insert(root->right, oldspeak, newspeak);
        }
        return root;
    }
    return node_create(oldspeak, newspeak);
}

void bst_print(Node *root) {
    if (root) {
        bst_print(root->left);
        printf("%s\n", root->oldspeak);
    }
}

void bst_delete(Node **root) {
    if (*root) {
        bst_delete(&(*root)->left);
        bst_delete(&(*root)->right);
        node_delete(root);
    }
}