#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/time.h>
#include <queue>
#include <iostream>
#include "Node.cpp"

#define  MAX_LINE_LENGTH 999 

void boundeddfs(state_t state, unsigned int bound, unsigned int limit, unsigned int &number, int hist) {
   state_t child;
   ruleid_iterator_t iter;
   int ruleid;
   if (bound == limit) {
      number++;
   } else {
      init_fwd_iter(&iter, &state);
      while((ruleid = next_ruleid(&iter)) >= 0) {
         apply_fwd_rule(ruleid, &state, &child);
         if (!fwd_rule_valid_for_history(hist,ruleid))
              continue;
         boundeddfs(child, bound+1, limit, number, next_fwd_history(hist,ruleid));
      }

   }
}


void iterativeddfs() {
   state_t state;
   unsigned int i;
   first_goal_state(&state,&i);
   unsigned int limit = 0;
   unsigned int numberOfNodes, previously;

   while (1) {
      numberOfNodes = 0;
      boundeddfs(state, 0, limit, numberOfNodes, init_history);
      if (limit > 0)
         cout << (float) numberOfNodes / previously << " ";

      std::cout << limit << " " << numberOfNodes << endl;
      previously = numberOfNodes;
      
      limit++;
   }
}



int main( int argc, char **argv ) {
   iterativeddfs();
} // end main
