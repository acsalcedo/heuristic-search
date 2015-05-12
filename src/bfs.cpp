#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/time.h>
#include <iostream>
#include <queue>
#include <limits>

#define  MAX_LINE_LENGTH 999 

using namespace std;

void breadthFirstSearch (state_t state) {

    state_t currentState, child;
    ruleid_iterator_t iter; 
    int ruleid;

    queue<state_t> q;
    state_map_t *map = new_state_map();

    q.push(state);
    state_map_add(map,&state,0);

    int *cost, *childCost;

    while (!q.empty()) {

        currentState = q.front();
        q.pop();
        
        cost = state_map_get(map,&currentState);

        if (is_goal(&currentState)) {
            cout << "Goal found: ";
            print_state(stdout,&currentState);
            cout << " Cost: " << *cost << endl;
            return;
        }

        init_fwd_iter(&iter,&currentState);

        while((ruleid = next_ruleid(&iter)) >= 0 ) {

            apply_fwd_rule(ruleid,&currentState,&child);

            childCost = state_map_get(map,&child);

            if (childCost == nullptr) {
                
                state_map_add(map,&child,*cost + get_fwd_rule_cost(ruleid));                
                q.push(child);
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

    breadthFirstSearch(state);
}












