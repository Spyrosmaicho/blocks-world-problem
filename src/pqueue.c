#include <stdio.h>
#include <stdlib.h>
#include "pqueue.h"

/* Hidden structs from user */
struct PQNodeTag {
    PQItem data;
    int priority;
    PQListNode next;
};

struct pqueue {
    int Count;
    PQListNode ItemList;
};

/* Initialize pqueue */
PriorityQueue pq_create(void) {
    PriorityQueue new = calloc(1, sizeof(struct pqueue));
    if(!new)
    {
        fprintf(stderr,"Problem allocating memory.\n");
        exit(1);
    }
    return new;
}

/* Returns true if pqueue is empty */
int pq_empty(PriorityQueue PQ) {
    return PQ->Count == 0;
}

/* Insert item into pqueue */
void pq_insert(PriorityQueue PQ, PQItem Item, int priority) {
    PQ->Count++;
    PQListNode new = calloc(1, sizeof(*new));
    if(!new)
    {
        fprintf(stderr,"Problem allocating memory.\n");
        exit(1);
    }
    new->data = Item;
    new->priority = priority;
    PQListNode prev = PQ->ItemList, next;
    
    //Insert at the head if the list is empty or Item has highest priority
    if (!prev || prev->priority >= new->priority) {
        new->next = prev;
        PQ->ItemList = new;
    }
    //Traverse list to find and put it into the correct position
    else 
    {
        while ((next = prev->next) && next->priority < new->priority) 
            prev = next;
        new->next = next;
        prev->next = new;
    }
}

/* Remove top item from pqueue */
PQItem pq_remove(PriorityQueue PQ) {
    PQItem temp;
    if (!pq_empty(PQ)) {
        temp = PQ->ItemList->data;
        PQListNode to_free = PQ->ItemList;
        PQ->ItemList = PQ->ItemList->next;
        free(to_free);
        PQ->Count--;
        return temp;
    }
    return 0;
}

/* Peek at the top of the pqueue */
PQItem pq_top(PriorityQueue PQ) {
    if (!pq_empty(PQ)) return PQ->ItemList->data;
    return 0;
}

/* Free everything in the pqueue */
void pq_destroy(PriorityQueue PQ) {
    PQListNode temp;
    while (!pq_empty(PQ)) {
        temp = PQ->ItemList;
        PQ->ItemList = PQ->ItemList->next;
        free(temp->data);
        free(temp);
        PQ->Count--;
    }
    free(PQ);
}