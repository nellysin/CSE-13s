#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <regex.h>
#include <ctype.h>

#include "node.h"
#include "salts.h"
#include "speck.h"
#include "bst.h"
#include "bf.h"
#include "bv.h"
#include "parser.h"
#include "ht.h"
#include "messages.h"

#define OPTIONS "hst:f:"
#define WORD    "[a-zA-Z0-9_'-]+"

//CITE: Professor Long in assignment doc
//CITE: TA Eugene for scanning

void menu(void) { //helper function to print the menu messages
    printf("SYNOPSIS\n");
    printf("  A word filtering program for the GPRSC\n");
    printf("  Filters out and reports bad words parsed from stdin.\n");

    printf("\nUSAGE\n");
    printf("    ./banhammer [-hs] [-t size] [-f size]\n");

    printf("\nOPTIONS\n");
    printf("     -h		 Program usage and help.\n");
    printf("     -s		 Print program statistics.\n");
    printf("     -t size	 Specify hash table size (default: 2^16).\n");
    printf("     -f size     Specify Bloom filter size (default: 2^20).\n");
}

//this function read in the list of oldspeak and newspeak pairs with fscanf()
//the oldspeak is only added the the bloom filter while the newspeak oldspeak are added to the hashtable
//the list of oldspeak pairs will be the newspeak.txt and vice versa
void scan_badspeak(BloomFilter *bf, HashTable *ht) { //helper function to scan the badspeak
    FILE *badspeakfile = stdin; //

    badspeakfile = fopen("badspeak.txt", "r");
    char bad_words[1024]; //buffer blocks are cited in asgn 6
    if (badspeakfile == NULL) {
        fprintf(stderr, "Error: unable to read file.\n");

        bf_delete(&bf);
        ht_delete(&ht);

        fclose(badspeakfile);
        exit(1);
    }
    while (fscanf(badspeakfile, "%s\n", bad_words) != EOF) {
        bf_insert(bf, bad_words);
        ht_insert(ht, bad_words, NULL);
    }
    fclose(badspeakfile);
    return;
}

//this function read in the list of oldspeak and newspeak pairs with fscanf()
//the oldspeak is only added the the bloom filter while the newspeak oldspeak are added to the hashtable
//the list of oldspeak pairs will be the newspeak.txt and vice versa
void scan_oldnew(BloomFilter *bf, HashTable *ht) {
    FILE *newspeakfile = stdin;

    newspeakfile = fopen("newspeak.txt", "r");
    char old_words[1024];
    char new_words[1024];

    if (newspeakfile == NULL) {
        fprintf(stderr, "Error: unable to read file.\n");
        bf_delete(&bf);
        ht_delete(&ht);
        fclose(newspeakfile);
        exit(1);
    }
    while (fscanf(newspeakfile, "%s %s\n", old_words, new_words)
           == 2) { //while there is two values of inputs then continue inserting to br and ht.
        bf_insert(bf, old_words);
        ht_insert(ht, old_words, new_words);
    }
    fclose(newspeakfile);
    return;
}

int main(int argc, char *argv[]) {
    bool stats = false;
    uint32_t bfSize = pow(2, 20);
    uint32_t htSize = pow(2, 16);

    //these are the command lines
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': menu(); return 0;
        case 's': stats = true; break;
        case 't': htSize = atoi(optarg); break;
        case 'f': bfSize = atoi(optarg); break;
        default: menu(); return 0;
        }
    }

    BloomFilter *bf = bf_create(bfSize);

    HashTable *ht = ht_create(htSize);

    scan_badspeak(bf, ht);

    scan_oldnew(bf, ht);

    //lexicon of badspeak and oldspeak/newspeak translations has been populated and start filter out words
    //this is done so by using the parsing module
    regex_t re;
    if (regcomp(&re, WORD, REG_EXTENDED)) {
        fprintf(stderr, "Failed to compile regex.\n");
        return 1;
    }

    char *word = NULL;

    Node *root = bst_create();
    Node *temp = bst_create();

    bool newspeak_translate = false;
    bool commit_crime = false;
    bool probe = false;

    //if the word is most likely been added to the bloom filter, bf_probe() returned true
    //no further action needs to be taken
    //However, if the ht contains the word does not have the newspeak translation then the citizen who use the word
    //is guilty of thought crime and insert the badspeak word in the list of badspeak and notify them with a message
    //this is the same with the oldspeak words with newspeak transtion.
    while ((word = next_word(stdin, &re)) != NULL) {
        for (uint32_t i = 0; i < strlen(word); i += 1) {
            word[i] = tolower(word[i]);
        }
        if (bf_probe(bf, word)) {
            probe = true;
            temp = ht_lookup(ht, word);
            if (temp != NULL && temp->newspeak != NULL) {
                newspeak_translate = true;
                root = bst_insert(root, word, temp->newspeak);
            } else {

                commit_crime = true;
                root = bst_insert(root, word, NULL);
            }
        }
    }

    if (stats
        == true) { // these are the statistics of the program include the bst size, height, average branches, ht load, bf load.
        float average = ((float) branches / lookups);
        float htLoad = 100 * ((float) ht_count(ht) / ht_size(ht));
        float bstLoad = 100 * ((float) bf_count(bf) / bf_size(bf));

        fprintf(stdout, "Average BST size: %7.6lf\n", ht_avg_bst_size(ht));
        fprintf(stdout, "Average BST height: %7.6lf\n", ht_avg_bst_height(ht));
        fprintf(stdout, "Average branches traversed: %7.6lf\n", average);
        fprintf(stdout, "Hash table load: %7.6lf%%\n", htLoad);
        fprintf(stdout, "Bloom filter load: %7.6lf%%\n", bstLoad);

        clear_words();
        regfree(&re);

        ht_delete(&ht);
        bf_delete(&bf);

        bst_delete(&root);

        return 0;
    }

    //using a boolean, for printing the goodspeak_message, mixspeak_message, and badspeak_message.
    if (probe == true && commit_crime == false && newspeak_translate == false) {
        printf("%s", goodspeak_message);
        bst_print(root);
    }

    else if (commit_crime == true && newspeak_translate == true) {
        printf("%s", mixspeak_message);
        bst_print(root);
    }

    else if (commit_crime == true && newspeak_translate == false) {
        printf("%s", badspeak_message);
        bst_print(root);
    }

    //clear memories

    bst_delete(&root);

    ht_delete(&ht);
    bf_delete(&bf);

    regfree(&re);
    clear_words();
    return 0;
}
