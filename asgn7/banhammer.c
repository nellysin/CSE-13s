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

//CITE: Professor Long in assignment doc -- instructions
//CITE: TA Eugene for scanning, understanding the structure, and the bfSize and htSize -- (from TA sections)
//CITE: TA Omar for understanting of regex, WORD, and printing alphabetically

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
    FILE *badspeakfile = stdin; //this is the file* for the stdin

    badspeakfile = fopen("badspeak.txt", "r"); //opening the badspeak.txt
    char bad_words[1024]; //buffer blocks are cited in asgn 6
    if (badspeakfile == NULL) {
        fprintf(stderr, "Error: unable to read file.\n");

        bf_delete(&bf); //we must delete the ht and bf if the badspeak file does not exist
        ht_delete(&ht);

        fclose(badspeakfile); //close the badspeak file
        exit(1);
    }
    while (fscanf(badspeakfile, "%s\n", bad_words)
           != EOF) { //this part is to scan the words in the badspeakfile
        bf_insert(bf,
            bad_words); //when we scan the badspeak.txt we are inserting them into the bf and ht (ht is for oldwords AND new words, however there is no new words and our badword is our oldword)
        ht_insert(ht, bad_words, NULL);
    }
    fclose(badspeakfile); //close the file before exiting the function (no leakage)
    return;
}

//this function read in the list of oldspeak and newspeak pairs with fscanf()
//the oldspeak is only added the the bloom filter while the newspeak oldspeak are added to the hashtable
//the list of oldspeak pairs will be the newspeak.txt and vice versa
void scan_oldnew(BloomFilter *bf, HashTable *ht) {
    FILE *newspeakfile = stdin; //file star for the stdin

    newspeakfile = fopen("newspeak.txt", "r"); //we will open the newspeak.txt
    char old_words[1024]; //this is our buffer for old_words AND new_words
    char new_words[1024];

    if (newspeakfile
        == NULL) { //if the newspeak file does not exist we must print an error message and exit the program with no memory leaks
        fprintf(stderr, "Error: unable to read file.\n");
        bf_delete(&bf);
        ht_delete(&ht);
        fclose(newspeakfile);
        exit(1);
    }
    while (
        fscanf(newspeakfile, "%s %s\n", old_words, new_words) //fscanf the words in the newspeak.txt
        != EOF) { //while there is two values of inputs then continue inserting to br and ht (we can use EOF similar to how we're scanning the badspeak words) until end of file
        bf_insert(bf, old_words); //we must insert the oldwords to the bf
        ht_insert(
            ht, old_words, new_words); //and insert the oldwords and new words in the hashtable
    }
    fclose(newspeakfile); //exit the helper function with no memory leaks
    return;
}

int main(int argc, char *argv[]) {
    bool stats = false;

    uint32_t bfSize = 0;
    bfSize = 1 << 20; //shift the bit 20 times by the wpoer of 2

    uint32_t htSize = 0;
    htSize = 1 << 16; //shift the bit 16 times by the power of 2

    //these are the command lines
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': menu(); return 0; //this is to print the menu
        case 's': stats = true; break; //this is for statistics (boolean)
        case 't':
            htSize = atoi(optarg);
            break; //using atoi (similar to asgn6) to change the string arg to an integer type
        case 'f':
            bfSize = atoi(optarg);
            break; //using the atoi (similar to adgn6) to change the string arg to an integer type
        default: menu(); return 0; //the default is printing the menu
        }
    }

    BloomFilter *bf = bf_create(bfSize); //initialize our bloom filter bf

    HashTable *ht = ht_create(htSize); //initialize our hashtable ht

    scan_badspeak(bf,
        ht); //call the helper function for badspeak to scan and store our words to the ht and bf

    scan_oldnew(bf,
        ht); //call the helper function for newspeak to scan and store our words to the ht and bf

    //lexicon of badspeak and oldspeak/newspeak translations has been populated and start filter out words
    //this is done so by using the parsing module
    regex_t re; //this is important to parse our words (given by asgn doc)
    if (regcomp(&re, WORD, REG_EXTENDED)) { //our pointer to a compuled regular expression
        fprintf(stderr, "Failed to compile regex.\n");
        return 1;
    }

    char *word = NULL;

    Node *root = bst_create(); //initialize the root for our bst_create();
    Node *temp = bst_create(); //initialize a temp for our bst_create();

    bool newspeak_translate = false; //these to indicate what are goodspeak, badspeak, and mixspeak
    bool commit_crime = false;
    bool probe = false; //ht_lookup

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
        float average = ((float) branches / lookups); //for brranches / lookups
        float htLoad
            = 100 * ((float) ht_count(ht) / ht_size(ht)); //for 100 * ht_count() / ht_size()
        float bstLoad
            = 100 * ((float) bf_count(bf) / bf_size(bf)); // for 100 * bf_count() / bf_size()

        fprintf(
            stdout, "Average BST size: %7.6lf\n", ht_avg_bst_size(ht)); //print the average bst size
        fprintf(stdout, "Average BST height: %7.6lf\n",
            ht_avg_bst_height(ht)); //print the average bst height
        fprintf(stdout, "Average branches traversed: %7.6lf\n", average); //print the average
        fprintf(stdout, "Hash table load: %7.6lf%%\n", htLoad); //print the ht load
        fprintf(stdout, "Bloom filter load: %7.6lf%%\n", bstLoad); //print the bst load
        //fprintf -- testing (gnuplot)
        //"%%" this is how we a printing the percent signs

        clear_words(); //clear and free any ht,bf, regex, words, and bst for no memory leaks
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
