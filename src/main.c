#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "state.h"
#include "pqueue.h"

int main(void) {

    int choice;
    /*User chooses a heuristic*/
    printf("Which heuristic algorithm you want(1-2): ");
    if(scanf("%d",&choice)!=1) 
    {
        fprintf(stderr,"No number given.\n");
        return 1;
    }

    if(choice!=1 && choice!=2) 
    {
        fprintf(stderr,"Wrong number for heuristic.\n");
        return 1;
    }

    /* Get block count */
    printf("\nGive the number of cubes: ");
    if (init_blocks()) return 1;
    PriorityQueue pq = pq_create();
    PriorityQueue pq2 = pq_create();

    /* Initial State */
    CState initial_c = cstate_create();
    printf("\nType the initial state: ");
    if (cstate_stdin(initial_c)) return 1;

    /* End State */
    CState end_c = cstate_create();
    printf("\nType the goal state: ");
    if (cstate_stdin(end_c)) return 1;


    printf("\n");

    /* States */
    State temp = state_create();
    state_load(temp, initial_c);
    puts("Initial state:");
    state_print_compact(temp);
    putchar('\n');
    State end = state_create();
    state_load(end, end_c);
    puts("Goal state:");
    state_print_compact(end);
    putchar('\n');


    switch(choice)
     {   case 1:
            /* Setup initial state */
            state_setpenalty1(temp, end);
            state_store(temp, initial_c);
            pq_insert(pq, initial_c, cstate_getpriority(initial_c));
            /* A* algorithm */
            CState prev = initial_c;
            while (state_cmp1(temp, end)) 
            {
                state_expand1(temp, end, pq, prev);
                prev = pq_remove(pq);
                state_load(temp, prev);
                pq_insert(pq2, prev, 1);
            }
            break;
        case 2:
            /* Setup initial state */
            state_setpenalty2(temp, end);
            state_store(temp, initial_c);
            pq_insert(pq, initial_c, cstate_getpriority(initial_c));
            /* Second Heuristic */
            CState prev2 = initial_c;
            while (state_cmp2(temp, end)) 
            {
                state_expand2(temp, end, pq, prev2);
                prev2 = pq_remove(pq);
                state_load(temp, prev2);
                pq_insert(pq2, prev2, 1);
            }
            break;
    }

    /* Print solution */
    printf("\nRequired Moves: %d\n\n", state_getmoves(temp));
    state_print_moves(temp);
    puts("\n");

    /* Deallocate memory */
    free(end_c);
    state_destroy(temp);
    state_destroy(end);
    pq_destroy(pq);
    pq_destroy(pq2);
}