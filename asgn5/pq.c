#include "pq.h"
#include "node.h"

#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>

//CITE: Professor Long for Priority Queue during lecture
//CITE: TA Eugene

struct PriorityQueue {
    uint32_t capacity;
    uint32_t tail;
    Node **items;
};

//Constructor for priority queue
PriorityQueue *pq_create(uint32_t capacity) {
    PriorityQueue *q = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    if (q) {
        q->tail = 0;
        q->capacity = capacity;
        q->items = (Node **) calloc(capacity, sizeof(Node));
        if (!q->items) {
            free(q);
            q = NULL;
        }
    }
    return q;
}
void pq_delete(PriorityQueue **q) {
    free(*q);
    *q = NULL;
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

bool enqueue(PriorityQueue *q, Node *n) { //CITE: TA Eugene for enqueue sudo code
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
        q->tail += 1;
        while (q->tail > 1 
               && q->items[parent]->frequency
                      < q->items[parent / 2]->frequency) { //while k > 1 <- this will be the index and comparing the frequency
            Node *temp = node_create(0, 0); //if the parent frequency is smaller then swap by creating a temporary node
            temp = q->items[parent / 2]; // place the [parent / 2] into the temp
            q->items[parent / 2] = q->items[parent]; //the [parent] will be assigned to [parent / 2]
            q->items[parent] = temp; // then assign temp to [parent]
            parent = (parent / 2); //parent = floor(k/2)
        }
        return true;
    }
}

void heapify(
    PriorityQueue *q, uint32_t parent) { //CITE: TA Eugene & Tutor Ben for heapify and dequeue
    uint32_t left = (parent * 2);
    uint32_t right = (left + 1);
    uint32_t min = parent;

    if ((left < q->capacity)
        && (q->items[min]->frequency
            < q->items[left]
                  ->frequency)) { //check if the left freq is less than parent and a stop function for capacity
        min = left;
    }
    if ((right < q->capacity)
        && (q->items[min]->frequency
            < q->items[right]->frequency)) { //check if the right freq is less than parent
        min = right; //make min to the right freq.
    }
    if (min != parent) { //when the min isn't parent
        Node *temp = node_create(0, 0); //this is swapping using a new Node *temp
        temp = q->items[parent];
        q->items[parent] = q->items[min];
        q->items[min] = temp;
        heapify(q, min);
    }
    return;
}

bool dequeue(PriorityQueue *q, Node **n) { //CITE Ben for help on fix heap and dequeue
    if (pq_empty(q) == true) { //return false when pq is empty
        return false;
    }
    *n = q->items[0];
    q->items[0] = q->items[q->tail - 1];
    q->tail -= 1;
    heapify(q, 0);
    return true;
}

void pq_print(PriorityQueue *q) {
    for (uint32_t i = 0; i < q->tail; i += 1) {
        printf("%lu", q->items[i]->frequency);
    }
}
