#include "pq.h"
#include "node.h"

#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>

//CITE: Professor Long for Priority Queue during lecture
//CITE: TA Eugene for pseudo code

//Most of these are referencing stack.c but credit goes to the help from Professor Long and TA Eugene
struct PriorityQueue {
    uint32_t capacity; //the capcity of the priority queue
    uint32_t tail; //this will be keeping track of the size
    Node **items;
};

//Constructor for priority queue
PriorityQueue *pq_create(uint32_t capacity) {
    PriorityQueue *q = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    if (q) {
        q->tail = 0;
        q->capacity = capacity;
        q->items = (Node **) calloc(capacity, sizeof(Node *));
        if (!q->items) { //free if there is no items
            free(q);
            q = NULL;
        }
    }
    return q;
}
void pq_delete(PriorityQueue **q) { //CITE: TA Eugene
    if (*q && (*q)->items) { //for freeing the memory
        free((*q)->items);
        free(*q);
        *q = NULL;
    }
    return;
}

bool pq_empty(PriorityQueue *q) {
    if (q->tail == 0) { //if pq head and pq tails is 0 then return true
        return true;
    } else {
        return false;
    }
}

bool pq_full(PriorityQueue *q) { //FIFO elements are dequeued at tail
    if (q->tail == q->capacity) {
        return true;
    } else {
        return false;
    }
}

uint32_t pq_size(PriorityQueue *q) { //returning the size of priority queue
    return q->tail;
}

bool enqueue(PriorityQueue *q,
    Node *n) { //CITE: TA Eugene for enqueue sudo code & referencing build heap in asgn3
    if (pq_full(q) == true) { //if it is full
        return false;
    }
    if (pq_empty(q) == true) { //if it is empty
        q->items[q->tail] = n;
        q->tail += 1;
        return true;
    } else {
        int parent = q->tail; //initialize parent to q->tail (make it a little cleaner)
        q->items[parent] = n; //assign items[parent] to the node
        q->tail += 1; //increment tail by 1
        while (
            q->tail > 1
            && q->items[parent]->frequency
                   < q->items[parent / 2]
                         ->frequency) { //while k > 1 <- this will be the index and comparing the frequency
            Node *temp = q->items[parent]; // place the [parent / 2] into the temp
            q->items[parent] = q->items[parent / 2]; //the [parent] will be assigned to [parent / 2]
            q->items[parent / 2] = temp; // then assign temp to [parent]
            parent = (parent / 2); //parent = floor(k/2)
        }
        return true;
    }
}

void fix_heap(PriorityQueue *q,
    uint32_t parent) { //CITE: TA Eugene, Tutor Ben, & Tutor Eric for heapify and dequeue
    uint32_t min = parent; //min is the parent
    uint32_t left = (min * 2); // left is min * 2
    uint32_t right = (left + 1); //right is (min * 2) + 1

    if ((left
            < q->capacity) //check if the left is less than the capacity and if the minimum frequency
        && (q->items[min]->frequency
            > q->items[left]
                  ->frequency)) { //check if the left freq is less than parent and a stop function for capacity
        min = left;
    } else {
        min = parent; //min will stay as parent
    }
    if ((right < q->capacity)
        && (q->items[min]->frequency
            > q->items[right]->frequency)) { //check if the right freq is less than parent
        min = right; //make min to the right freq.
    } else {
        min = parent; //min will stay as parent
    }
    if (min != parent) { //when the min isn't parent
        Node *temp = q->items[min]; //assign [parent] to temp
        q->items[min] = q->items[parent]; // assign the parent frequency to min
        q->items[parent] = temp; //assign the parent node to the temp
        fix_heap(q, min); // recursively call & the this function until it reaches capacity
    }
    return;
}

//CITE: TA Eugene & Tutor Eric for heapify and dequeue
bool dequeue(PriorityQueue *q, Node **n) { //CITE Ben for help on fix heap and dequeue
    if (pq_empty(q) == true) { //return false when pq is empty
        return false;
    }
    //setting item to the lowest frequency
    *n = q->items[0];
    q->items[0] = q->items[q->tail - 1];
    q->tail -= 1;
    fix_heap(q, 0);
    return true;
}

//void pq_print(PriorityQueue *q) {
//    for (uint32_t i = 0; i < q->tail; i += 1) {
//        printf("%lu", q->items[i]->frequency);
//    }
//}
