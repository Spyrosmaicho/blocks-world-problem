#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pqueue.h"
#include "state.h"
#include "vector.h"

/* Holds how many blocks the problem has */
int block_count;

/* Structs hidden from user */
struct state {
    Vector blocks[26];
    int moves;
    int penalty;
    CState parent;
};

struct state_compact {
    char block_string[52];
    int moves;
    int penalty;
    CState parent;
};

/* Get number of blocks from stdin */
int init_blocks(void) {
    if (scanf("%d", &block_count) != 1) return 1;
    if (block_count > 26) return 1; /* 26 is max for all letters of latin */
    return 0;
}

/* Intialize a state */
State state_create(void) {
    State new = calloc(1, sizeof(struct state));
    if(!new)
    {
        fprintf(stderr,"Problem allocating memory.\n");
        exit(1);
    }
    for (int i = 0 ; i < block_count ; ++i) {
        new->blocks[i] = vector_create(block_count + 1);  /* Create vector for each block */
    }
    return new;
}

/* Intialize a compact state */
CState cstate_create(void) {
    return calloc(1, sizeof(struct state_compact));
}

/* Returns how many moves state has done */
int state_getmoves(State state) {
    return state->moves;
}

/* Calculates priority for compact state */
int cstate_getpriority(CState state) {
    return state->moves + state->penalty;
}

/* Creates a compact state from user input */
int cstate_stdin(CState state) {
    char buffer[27] = {0};
    int count = 0, j = 0;
    char *str = state->block_string;
    while (count != block_count) {
        if (scanf("%26s", buffer) != 1) return 1;
        int len = strlen(buffer);
        sprintf(str + j, "%s", buffer); 
        count += len;
        j += len + 1;
    }
    return 0;
}

/* Prints state in a compact form */
void state_print_compact(State state) {
    for (int i = 0 ; i < block_count ; ++i) {
        char *tower = vector_array(state->blocks[i]);
        if (!tower[0]) continue; /* Skiping empty towers */
        int j = -1;
        while (++j < block_count && tower[j]) printf("%c", tower[j]);
        putchar(' ');
    }
}

/* Recursive print moves of state */
void state_print_movesR(CState state, State temp) {
    if (!state) return;
    CState parent = state->parent;
    state_print_movesR(parent, temp);
    state_load(temp, state);
    state_print_compact(temp);
    puts("->");
}

/* Print the moves required to get to state */
void state_print_moves(State state) {
    State temp = state_create();
    state_print_movesR(state->parent, temp);
    state_print_compact(state);
    state_destroy(temp);
}

/* Store state in the compact form */
void state_store(State state, CState dest) {
    dest->moves = state->moves;
    dest->penalty = state->penalty;
    dest->parent = state->parent;
    memset(dest->block_string, 0, block_count * 2 * sizeof(char));
    for (int i = 0, j = 0 ; j < block_count ; ++j) {
        char *tower = vector_array(state->blocks[j]);
        int len = strlen(tower);
        strcat(dest->block_string + i, tower);
        i += len + 1;
    }
}

/* Load state from the compact form */
void state_load(State state, CState src) {
    state->moves = src->moves;
    state->penalty = src->penalty;
    state->parent = src->parent;
    for (int i = 0, j = 0 ; j < block_count ; ++j) {
        char *tower = vector_array(state->blocks[j]);
        memset(tower, 0, (block_count + 1) * sizeof(char));
        int len = strlen(src->block_string + i);
        strcpy(tower, src->block_string + i);
        vector_set_size(state->blocks[j], len);
        i += len + 1;
    }
}

/* Calculate penalty based on heuristic provided by assignment */
int state_cmp1(State curr, State end) {
    int penalty = 0;
    for (int i = 0 ; i < block_count ; ++i) {
        char *tower = vector_array(curr->blocks[i]);
        int to_add = strlen(tower);
        if (to_add == 0) continue;
        for (int j = 0 ; j < block_count ; ++j) {
            char *to_cmp = vector_array(end->blocks[j]);
            if (to_cmp[0] == tower[0]) {
                int end = to_add;
                for (int k = 0 ; k < end ; ++k) {
                    if (to_cmp[k] == tower[k]) --to_add;
                }
                break;
            }
        }
        penalty += to_add;
    }
    return penalty;
}


/* 
 *  Calculate penalty 
* This heuristic calculates the penalty based on the number of blocks that need to be moved once or twice.
 *  A block that must be moved once is a block that is currently on a block different from the one 
 * it rests on in the goal state or has such a block somewhere below it in the same pile.
 *  A block that must be moved twice is a block that is currently on the block it must be placed on in the goal state,
 * but that block must be moved or if there exists a block that must be moved twice somewhere below it .
 */

int state_cmp2(State curr, State end) {
    int penalty = 0;
    for (int i = 0 ; i < block_count ; ++i) {
        char *tower = vector_array(curr->blocks[i]);
        int to_add = strlen(tower);
        if (to_add == 0) continue;
        for (int j = 0 ; j < block_count ; ++j) {
            char *to_cmp = vector_array(end->blocks[j]);
            if (to_cmp[0] == tower[0]) {
                int k = 0;
                while (to_cmp[k] == tower[k]) {
                    ++k;
                    if (--to_add == 0) break;
                }
                break;
            }
        }
        penalty += to_add;
    }
    return penalty;
}


/* Set penalty for curr state based on end state */
void state_setpenalty1(State curr, State end) {
    curr->penalty = state_cmp1(curr, end);
}

/* Set penalty for curr state based on end state */
void state_setpenalty2(State curr, State end) {
    curr->penalty = state_cmp2(curr, end);
}

/* Make all possible moves for curr state and add them to pqueue */
void state_expand1(State curr, State end, PriorityQueue pq, CState prev) {
    for (int i = 0 ; i < block_count ; ++i) {
        if (vector_size(curr->blocks[i]) == 0) continue; /* Empty tower */
        int did_table = vector_size(curr->blocks[i]) == 1; /* If it was on table initialize as 1 */
        char to_put = vector_pop(curr->blocks[i]);
        for (int j = 0 ; j < block_count ; ++j) {
            if (i == j) continue;
            Vector tower = curr->blocks[j];
            if (vector_size(tower) == 0) {
                if (did_table) continue;
                did_table = 1;
            }
            /* Make the move, store it and push to pqueue */
            vector_push_back(tower, to_put);
            CState new = cstate_create();
            state_store(curr, new);
            new->moves = curr->moves + 1;
            new->penalty = state_cmp1(curr, end);
            new->parent = prev;
            pq_insert(pq, new, cstate_getpriority(new));
            /* Backtrack */
            vector_pop(tower);
        }
        /* Backtrack */
        vector_push_back(curr->blocks[i], to_put);
    }
}


void state_expand2(State curr, State end, PriorityQueue pq, CState prev) {
    for (int i = 0 ; i < block_count ; ++i) {
        if (vector_size(curr->blocks[i]) == 0) continue; /* Empty tower */
        int did_table = vector_size(curr->blocks[i]) == 1; /* If it was on table initialize as 1 */
        char to_put = vector_pop(curr->blocks[i]);
        for (int j = 0 ; j < block_count ; ++j) {
            if (i == j) continue;
            Vector tower = curr->blocks[j];
            if (vector_size(tower) == 0) {
                if (did_table) continue;
                did_table = 1;
            }
            /* Make the move, store it and push to pqueue */
            vector_push_back(tower, to_put);
            CState new = cstate_create();
            state_store(curr, new);
            new->moves = curr->moves + 1;
            new->penalty = state_cmp2(curr, end);
            new->parent = prev;
            pq_insert(pq, new, cstate_getpriority(new));
            /* Backtrack */
            vector_pop(tower);
        }
        /* Backtrack */
        vector_push_back(curr->blocks[i], to_put);
    }
}

/* Free allocated memory for state */
void state_destroy(State state) {
    for (int i = 0 ; i < block_count ; ++i) {
        vector_free(state->blocks[i]);
    }
    free(state);
}