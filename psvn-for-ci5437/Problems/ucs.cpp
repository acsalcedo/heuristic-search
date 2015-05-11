#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/time.h>
#include <queue>
#include <iostream>

using namespace std;

uniform-cost-search(state_t state):
	
	pair<std::state_t,unsigned int> pair;
	priority_queue<pair<state_t,unsigned int>, vector<pair<state_t,unsigned int>>, CompareCosts> pq;

	state_map_t *map = new_state_map();
	state_map_add(map, &state, 0);
	
	pair.first = state;
	pair.second = 0;	
	pq.push(pair);

	ruleid_iterator_t iter;
	unsigned int dist;
	int ruleid;
	
	while (!q.empty()) {
		
		pair<state_t,unsigned int> statecost;
		pair<state_t,unsigned int> child;
		
		statecost = pq.top();
		pq.pop();
		
		if (is_goal(&statecost.first)) 
			return statecost.first;

		init_fwd_iter(&iter, &statecost.first);
         
         while((ruleid = next_ruleid(&iter)) >= 0) {
         	
         	apply_fwd_rule(ruleid, &statecost.first, &child.first);
         	dist = statecost.second + get_fwd_rule_cost(ruleid);
         	
         	int *cost = state_map_get(map, child.first);

         	if ( cost == NULL)
         		state_map_add(map, &child, dist);
         	else if (dist < *cost){
         		state_map_add(map,&child,dist);
         		// REPLACEEEEEEEEE RE}
         	}

	}




int main( int argc, char **argv ) {
//READ A LINE OF INPUT FROM stdin
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
