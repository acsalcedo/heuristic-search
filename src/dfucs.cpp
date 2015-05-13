#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/time.h>
#include <iostream>
#include <limits>

#define  MAX_LINE_LENGTH 999 

using namespace std;

pair<state_t*, int> boundedDfs(state_t state, int bound, int cost, int hist) {

    int ruleid;
    state_t child;
    ruleid_iterator_t iter;
    
    if (cost > bound)
        return make_pair(nullptr,cost);

    if (is_goal(&state)) {
        pair<state_t*, int> p2 = make_pair(&state,cost);
        print_state(stdout,p2.first);
        return p2;
    }

    int t = INT_MAX;

    init_fwd_iter(&iter,&state);
         
    while((ruleid = next_ruleid(&iter)) >= 0) {
        apply_fwd_rule(ruleid,&state, &child);

        if (!fwd_rule_valid_for_history(hist,ruleid))
            continue;

        int newCost = cost+get_fwd_rule_cost(ruleid);

        pair<state_t*, int> n = boundedDfs(child,bound,newCost,next_fwd_history(hist,ruleid));
        
        if (n.first != nullptr) 
            return make_pair(n.first, n.second);

        t = min(t,n.second);
    }
    return make_pair(nullptr,t);       

}

int main( int argc, char **argv ) {

    char str[ MAX_LINE_LENGTH +1 ] ;
    ssize_t nchars; 
    state_t state; // state_t is defined by the PSVN API. It is the type used for individual states.

    state_t child;
    ruleid_iterator_t iter; // ruleid_terator_t is the type defined by the PSVN API successor/predecessor iterators.
    int ruleid ; // an iterator returns a number identifying a rule
    int childCount = 0;
    
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

    int bound = 0;

    while (true) {

       pair<state_t*, int> p = boundedDfs(state,bound,0,init_history);

       if (p.first != nullptr) {
           cout << "Cost: " << p.second << "\n";
           return p.second;
       }

       bound = p.second;
       
    }

}