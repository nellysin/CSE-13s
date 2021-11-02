#include "pq.h"
#include "node.h"

#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>

//CITE: Professor Long for Priority Queue during lecture
//CITE: TA Eugene

struct PriorityQueue{
	uint32_t capacity;
	uint32_t tail;
	Node **items;
};

//Constructor for priority queue
PriorityQueue *pq_create(uint32_t capacity){
	PriorityQueue *q = (PriorityQueue *)malloc(sizeof(PriorityQueue));
	if(q){
		q->tail = 0;
		q->capacity = capacity;
		q->items = (Node **)calloc(capacity, sizeof(Node));
		if(!q->items){
			free(q);
			q = NULL;
		}
	}
	return q;
}
void pq_delete(PriorityQueue **q){
	free(*q);
	*q = NULL;
}

bool pq_empty(PriorityQueue *q){
	if(q->tail == 0){ //if pq head and pq tails is 0 then return true
		return true;
	}
	else{
		return false;
	}
}

bool pq_full(PriorityQueue *q){  //FIFO elements are dequeued at tail
	if(q->tail == q->capacity){
		return true;
	}
	else{
		return false;
	}
}

uint32_t pq_size(PriorityQueue *q){ //returning the size of priority queue
	return q->tail;
}

bool enqueue(PriorityQueue *q, Node *n){ //CITE: TA Eugene for enqueue sudo code
	if(pq_full(q) == true){
		return false;
	}
	if(q->tail == 0){
		q->items[q->tail] = n;
		q->tail += 1;
		return true;
	}
	else{
		int parent = q->tail;
		q->items[parent] = n;
		q->tail += 1;
		while(parent > 1){ //while k > 1 <- this will be the index
			parent = (parent/2); //parent = floor(k/2)
			if(n->frequency < q->items[parent]->frequency){
				Node *temp = node_create(0,0);
				temp = q->items[parent];
				q->items[parent] = n;
				n = temp;
			}
		}
		return true;
	}
}



//bool dequeue(PriorityQueue *q, Node **n){

//}

//void pq_print(PriorityQueue *q){

//}
