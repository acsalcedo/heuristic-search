#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/time.h>
#include <iostream>
#include "priority_queue.hpp"
#include <limits>

#define  MAX_LINE_LENGTH 999 

using namespace std;


int bestFirstSearch (state_t state) {

    state_t child;
    ruleid_iterator_t iter; 
    int ruleid;

    PriorityQueue<state_t> pq;
    state_map_t *map = new_state_map();

    pq.Add(0,0,state);
    state_map_add(map,&state,0);

    int distance = 0;

    while (!pq.Empty()) {

        state = pq.Top();
        pq.Pop();

        int *dist = state_map_get(map,&state);

        if (dist == nullptr || *dist < distance) {

            state_map_add(map,&state,*dist);

            if (is_goal(&state))
                return *dist;

            init_fwd_iter(&iter,&state);

            while((ruleid = next_ruleid(&iter)) >= 0 ) {

                apply_fwd_rule(ruleid,&state,&child);

                // TODO falta eliminar los duplicados
    
                // TODO if de heuristica

                if (dist == nullptr)
                    *dist = 0;

                int childCost = *dist +get_fwd_rule_cost(ruleid);
                
                pq.Add(childCost,childCost,child);
                state_map_add(map,&child,childCost);
            }
        }
    }
}

int main( int argc, char **argv ) {

    char str[MAX_LINE_LENGTH +1] ;
    ssize_t nchars; 
    state_t state; // state_t is defined by the PSVN API. It is the type used for individual states.
    
    printf("Please enter a state followed by ENTER: ");
    if ( fgets(str, sizeof str, stdin) == NULL ) {
        printf("Error: empty input line.\n");
        return 0; 
    }

    nchars = read_state( str, &state );
    if (nchars <= 0) {
        printf("Error: invalid state entered.\n");
        return 0; 
    }
   
    printf("The state you entered is: ");
    print_state(stdout, &state);
    printf("\n");

    int cost = bestFirstSearch(state);
}












