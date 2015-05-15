#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/time.h>
#include <queue>
#include <iostream>

#define  MAX_LINE_LENGTH 999 
using namespace std;

void boundeddfs(state_t state, unsigned int bound, unsigned int limit, unsigned int &number, int hist, int prunning) {
   state_t child;
   ruleid_iterator_t iter;
   int ruleid;
   if (bound == limit) {
      number++;
   } else {
      init_fwd_iter(&iter, &state);
      while((ruleid = next_ruleid(&iter)) >= 0) {
         apply_fwd_rule(ruleid, &state, &child);
         if (!fwd_rule_valid_for_history(hist,ruleid) && (prunning))
              continue;
         boundeddfs(child, bound+1, limit, number, next_fwd_history(hist,ruleid), prunning);
      }

   }
}


void iterativeddfs(int prunning) {
   state_t state;
   unsigned int i;
   first_goal_state(&state,&i);
   unsigned int limit = 0;
   unsigned int numberOfNodes, previously= 0;

   while (1) {
      numberOfNodes = 0;
      boundeddfs(state, 0, limit, numberOfNodes, init_history, prunning);
      if (limit > 0)
         cout << (float) numberOfNodes / previously << endl;

      std::cout << limit << " " << numberOfNodes << " ";
      previously = numberOfNodes;
      
      limit++;
   }
}



int main( int argc, char **argv ) {
   int i = atoi(argv[1]);
   cout << i << endl;
   iterativeddfs(i);
} // end main
