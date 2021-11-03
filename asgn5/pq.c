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
    if (q->tail == 0) {		//if it is empty
        q->items[q->tail] = n;
        q->tail += 1;
        return true;
    } else {
        int parent = q->tail; //the parent 
        q->items[parent] = n;
        q->tail += 1;
        while (parent > 1) { //while k > 1 <- this will be the index
            parent = (parent / 2); //parent = floor(k/2)
            if (n->frequency < q->items[parent]->frequency) {
                Node *temp = node_create(0, 0);
                temp = q->items[parent];
                q->items[parent] = n;
                n = temp;
            }
        }
        return true;
    }
}
void min_child(Node **f, first, last)

void fix_heap(Node **f, int first, int last){
	bool found = false;
	uint32_t left = parent * 2;
	uint32_t right = left + 1;
	uint32_t min = first;
	
	if(left <q->capacity && f[left]->frequency < f[parent]->frequency){ //check if the left freq is less than parent
		min = f[left]->frequency;
	}else{
		min = f[parent]->frequency; //the min is still the parent
	}
	if(f[right]->frequency < f[parent]->frequency){ //check if the right freq is less than parent
		min = f[right]->frequency; //make min to the right freq.
	} else{
		min = f[parent]->frequency; //make min to the parent freq
	}
	if(min != parent){	//when the min isn't parent
		Node *temp = node_create(0,0); //this is swapping using a new Node *temp
		temp = f[parent];
		f[parent] = f[min];
		f[min] = temp;
		found = true;
		}
}

*bool dequeue(PriorityQueue *q, Node **n) {  //CITE Ben for help on fix heap and dequeue
	if(pq_empty(q) == true){ //return false when pq is empty
		return false;
	}
	if(q->tail == 1){
		q->tail += 1;
		*n = q->items[0];
		return true;
	}
	*n = q->items[0];
	uint32_t s = (q->tail - 1);
	q->[0] = q->items[s];
	q->tail -= 1;
	fix_heap(q, 1);
	return true;
}

void pq_print(PriorityQueue *q) {
    for (uint32_t i = 0; i < q->tail; i += 1) {
        printf("%lu", q->items[i]->frequency);
    }
}
