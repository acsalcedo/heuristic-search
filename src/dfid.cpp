#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/time.h>
#include <queue>
#include <iostream>
#include <limits>
#include <algorithm>    // std::min
#define  MAX_LINE_LENGTH 999 

using namespace std;


// ESTE ESSSS DFSID
state_t* boundeddfs(state_t state, unsigned int bound, unsigned int depth, int hist) {
   state_t child, newState;
   ruleid_iterator_t iter;
   int ruleid;
   if (depth > bound) 
      return nullptr;

   if (is_goal(&state))
      return &state;

   init_fwd_iter(&iter, &state);
   while((ruleid = next_ruleid(&iter)) >= 0) {
      apply_fwd_rule(ruleid, &state, &child);
      if (!fwd_rule_valid_for_history(hist,ruleid))
           continue;
      state_t* n =  boundeddfs(child, depth+1, bound, next_fwd_history(hist,ruleid));
      if (n != nullptr)
         return n;

   }
   return nullptr;
}


void iterativeddfs(state_t state) {
   unsigned int bound = 0;

   while (1) {
      state_t* n = boundeddfs(state, 0, bound, init_history);
      if (n!= nullptr) {
         cout << "Goal found" << endl;
         return;
      }
      bound++;
   }
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
    iterativeddfs(state);
} // end main
