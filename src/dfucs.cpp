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

int depthFirstUCS(state_t state, int cost, int hist) {


	if (is_goal(state))
		return make_pair(state,cost);

	while((ruleid = next_ruleid(&iter)) >= 0 ) {

    	apply_fwd_rule(ruleid,&state,&child);

    	if (!fwd_rule_valid_for_history(hist,ruleid))
            continue;

        int newCost = cost+get_fwd_rule_cost(ruleid);

        pair<state*,int> n = depthFirstUCS(child,newCost,next_fwd_history(hist,ruleid));


      

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

    return depthFirstUCS(state,0,init_history);
}