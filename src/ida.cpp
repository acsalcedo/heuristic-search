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


pair<state_t*,unsigned int> boundDFS(state_t state, unsigned int cost, unsigned int bound, int hist) {

    state_t child;
    int ruleid;
    ruleid_iterator_t iter;

    unsigned int f = cost + h.getHeuristic4x4(state.vars);

    if (f > bound)
        return make_pair(nullptr,f);

    if (is_goal(&state))
        return make_pair(&state,cost);

    unsigned int t = UINT_MAX;

    init_fwd_iter(&iter,&state);
         
    while((ruleid = next_ruleid(&iter)) >= 0) {
        apply_fwd_rule(ruleid,&state, &child);

        if (!fwd_rule_valid_for_history(hist,ruleid))
            continue;

        pair<state_t*,unsigned int> n = boundDFS(child,cost+get_fwd_rule_cost(ruleid),bound,next_fwd_history(hist,ruleid));
        
        if (n.first != nullptr) 
            return make_pair(n.first, n.second);

        t = min(t,n.second);
    }

    return make_pair(nullptr,t);   
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

    pair<state_t*,int> p;

    while (true) {
        p = boundDFS(state,0,bound,init_history);
        if (p.first != nullptr) {
            cout << "Goal found with cost: " << p.second << endl;
            return 1;
        }   
        bound = p.second;            
    }

}