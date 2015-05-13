#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/time.h>
#include <iostream>
#include "priority_queue.hpp"
#include "heuristics.hpp"
#include <limits>

#define  MAX_LINE_LENGTH 999 
Heuristics h;
using namespace std;

void bestFirstSearch(state_t state) {

    PriorityQueue<state_t> pq;
    pq.Add(0,0,state);

    state_map_t *map = new_state_map();
    state_map_add(map,&state,0);

    state_t currentState, child;
    int * cost;
    int ruleid, priority, childCost;
    ruleid_iterator_t iter;

    while (!pq.Empty()) {

        priority = pq.CurrentPriority();

        currentState = pq.Top();
        pq.Pop();           

        cost = state_map_get(map,&currentState);

        if (cost != nullptr || priority < *cost) {

            /* The state added to map is Gray */
            state_map_add(map,&currentState,priority);

            if (is_goal(&currentState)) {
                cout << "Goal found: ";
                print_state(stdout,&currentState);
                cout << " Cost: " << priority << endl;
                return;
            }           

            init_fwd_iter(&iter,&currentState);

            while((ruleid = next_ruleid(&iter)) >= 0) {

                apply_fwd_rule(ruleid,&currentState,&child);

                if (h.getHeuristic4x4(child.vars) < UINT_MAX) {                
                    childCost = priority + get_fwd_rule_cost(ruleid);
                    state_map_add(map,&child,childCost);
                    pq.Add(childCost,childCost,child);
                }
            }           
        }
    }
    cout << "No goal found.\n";
}

int main( int argc, char **argv ) {

    char str[MAX_LINE_LENGTH +1] ;
    ssize_t nchars; 
    state_t state; // state_t is defined by the PSVN API. It is the type used for individual states.


    printf("Please enter a state followed by ENTER: ");
        if (fgets(str, sizeof str, stdin) == NULL) {
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

    h.initialize4x4();

    unsigned int bound = h.getHeuristic4x4(state.vars);

    bestFirstSearch(state);           

}