#ifndef PQUEUE_H_
#define PQUEUE_H_

#define ITEMFORMAT "%d"
typedef struct state_compact *PQItem;

typedef struct pqueue *PriorityQueue;
typedef struct PQNodeTag *PQListNode;

#include "state.h"


/* Initialize pqueue */
PriorityQueue pq_create(void);

/* Returns true if pqueue is empty */
int pq_empty(PriorityQueue PQ);

/* Insert item into pqueue */
void pq_insert(PriorityQueue PQ, PQItem Item, int priority);

/* Remove top item from pqueue */
PQItem pq_remove(PriorityQueue PQ);

/* Peek at the top of the pqueue */
PQItem pq_top(PriorityQueue PQ);

/* Free everything in the pqueue */
void pq_destroy(PriorityQueue PQ);

#endif