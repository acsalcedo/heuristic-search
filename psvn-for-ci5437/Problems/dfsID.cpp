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
state_map_t *map;

pair<state_t*, int> boundedDfs(state_t state, int bound, int hist) {

    int ruleid;
    state_t child;
    ruleid_iterator_t iter;
    
    int * cost = state_map_get(map, &state);

    if (cost != nullptr && *cost > bound)
        return make_pair(nullptr,*cost);

    if (is_goal(&state)) {
        cout << "\n";
        pair<state_t*, int> p2 = make_pair(&state,*cost);
        print_state(stdout,p2.first);
        return p2;
    }

    int t = INT_MAX;

    init_fwd_iter(&iter,&state);

    // cout << "Estado actual: ";
    // print_state(stdout,&state);
    // cout << " Costo: " << *cost << "\n";
         
    while((ruleid = next_ruleid(&iter)) >= 0) {
        apply_fwd_rule(ruleid,&state, &child);

        if (!fwd_rule_valid_for_history(hist,ruleid))
            continue;

        int newCost = *cost+get_fwd_rule_cost(ruleid);
//        cout << "fwd cost: " << newCost << "\n";

        int *childCost = state_map_get(map,&child);

        if(childCost == nullptr)
            state_map_add(map,&child,*cost+get_fwd_rule_cost(ruleid));

        pair<state_t*, int> n = boundedDfs(child,bound,next_fwd_history(hist,ruleid));
        
        if (n.first != nullptr) 
            return make_pair(n.first, n.second);

        t = min(t,n.second);
    }

    return make_pair(nullptr,t);        

}

int main( int argc, char **argv ) {
//VARIABLES FOR INPUT
    char str[ MAX_LINE_LENGTH +1 ] ;
    ssize_t nchars; 
    state_t state; // state_t is defined by the PSVN API. It is the type used for individual states.

// VARIABLES FOR ITERATING THROUGH state's SUCCESSORS
    state_t child;
    ruleid_iterator_t iter; // ruleid_terator_t is the type defined by the PSVN API successor/predecessor iterators.
    int ruleid ; // an iterator returns a number identifying a rule
    int childCount = 0;
    
//  READ A LINE OF INPUT FROM stdin
    printf("Please enter a state followed by ENTER: ");
    if ( fgets(str, sizeof str, stdin) == NULL ) {
        printf("Error: empty input line.\n");
        return 0; 
    }

//CONVERT THE STRING TO A STATE
    nchars = read_state( str, &state );
    if (nchars <= 0) {
        printf("Error: invalid state entered.\n");
        return 0; 
    }
   
    printf("The state you entered is: ");
    print_state(stdout, &state);
    printf("\n");

    int bound = 0;

    map = new_state_map();
    state_map_add(map,&state,0);

    while (true) {

       pair<state_t*, int> p = boundedDfs(state,bound,init_history);

       if (p.first != nullptr) {
           cout << "Cost: " << p.second << "\n";
           return p.second;
       }

       bound = p.second;

      // cout << "bound: " << bound << "\n";
       
    }

}