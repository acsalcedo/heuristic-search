#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/time.h>
#include <iostream>
#include <limits>

#define  MAX_LINE_LENGTH 999 

state_map_t *map = new_state_map();

using namespace std;

pair<state_t*,int> depthFirstUCS(state_t state, int cost, int hist) {

    int ruleid;
    state_t child;
    ruleid_iterator_t iter;

    int newCost;
    int *childCost;

    if (is_goal(&state)) {
        cout << "Goal found: ";
        print_state(stdout,&state);
        cout << " Cost: " << cost << endl;
        return make_pair(&state,cost);
    }    

    cout << "hola";
    unsigned int t = UINT_MAX;
    init_fwd_iter(&iter,&state);

    while ((ruleid = next_ruleid(&iter)) >= 0) {
        
        apply_fwd_rule(ruleid,&state,&child);
        
        if (!fwd_rule_valid_for_history(hist,ruleid))
            continue;

        childCost = state_map_get(map,&state);
        newCost = cost + get_fwd_rule_cost(ruleid);

        if (childCost == nullptr || newCost < *childCost) {
            state_map_add(map,&child,newCost);
            depthFirstUCS(child,newCost,next_fwd_history(hist,ruleid));   
        }
    }

    return make_pair(nullptr,0);
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

    pair<state_t*,int> p = depthFirstUCS(state,0,init_history);

    if (p.first != nullptr)
        cout << "Cost: " << p.second << endl;
    // if (p.first == nullptr) {
    //     cout << "No goal found.\n";
    // }
}