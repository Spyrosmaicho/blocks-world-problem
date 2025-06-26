#ifndef STATE_H_
#define STATE_H_
#include "pqueue.h"

typedef struct state *State;
typedef struct state_compact *CState;

/* Get number of blocks from stdin */
int init_blocks(void);

/* Intialize a state */
State state_create(void);

/* Intialize a compact state */
CState cstate_create(void);

/* Returns how many moves state has done */
int state_getmoves(State state);

/* Calculates priority for compact state */
int cstate_getpriority(CState state);

/* Creates a compact state from user input */
int cstate_stdin(CState state);

/* Prints state in a compact form */
void state_print_compact(State state);
/* Recursive print moves of state */
void state_print_movesR(CState state, State temp);

/* Print the moves required to get to state */
void state_print_moves(State state);

/* Store state in the compact form */
void state_store(State state, CState dest);

/* Load state from the compact form */
void state_load(State state, CState src);

/* Calculate penalty based on heuristic provided by assignment */
int state_cmp1(State curr, State end);

/*Calculate penalty based on heuristic2 */
int state_cmp2(State curr, State end);

/* Set penalty for curr state based on end state */
void state_setpenalty1(State curr, State end);
void state_setpenalty2(State curr, State end);

/* Make all possible moves for curr state and add them to pqueue */
void state_expand1(State curr, State end, PriorityQueue pq, CState prev);
void state_expand2(State curr, State end, PriorityQueue pq, CState prev);

/* Free allocated memory for state */
void state_destroy(State state);

#endif