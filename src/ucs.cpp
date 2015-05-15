#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/time.h>
#include <queue>
#include <iostream>
#include <fstream>
#include <string>
#include "priority_queue.hpp"
#include <time.h>

#define  MAX_LINE_LENGTH 999 

FILE *output;
unsigned long int nodes = 0;

using namespace std;

void uniformCostSearch(state_t *state) {

    PriorityQueue<state_t> pq;
    pq.Add(0,0,*state);

    state_map_t *map = new_state_map();
    state_map_add(map,state,0);

    state_t currentState, child;
    int * cost;
    int ruleid, priority, childCost;
    ruleid_iterator_t iter;

    while (!pq.Empty()) {

        priority = pq.CurrentPriority();

        currentState = pq.Top();
        pq.Pop();           

        nodes++;
        
        cost = state_map_get(map,&currentState);

        if (cost == nullptr || priority <= *cost) {

            /* The state added to map is Gray */
            state_map_add(map,&currentState,priority);

            if (is_goal(&currentState)) {
                fprintf(output, ": - %i %lu ", priority, nodes);
                destroy_state_map(map);
                return;
            }           

            init_fwd_iter(&iter,&currentState);

            while((ruleid = next_ruleid(&iter)) >= 0) {

                apply_fwd_rule(ruleid,&currentState,&child);
                
                childCost = priority + get_fwd_rule_cost(ruleid);
                state_map_add(map,&child,childCost);
                pq.Add(childCost,childCost,child);
            }           
        }
    }
    destroy_state_map(map);
    cout << "No goal found.\n";
}

int main( int argc, char **argv ) {

    if (argc < 3) {
        cout << "Use: ./<exec>.ucs <nameStatesFile> <outputFile>\n";
        return 0;
    }

    ifstream fileStates;
    fileStates.open(argv[1]);

    if (!fileStates.is_open()) {
        cout << "Error opening file containing states.\n";
        return 0;
    }

    output = fopen(argv[2],"w");
    
    if (output == nullptr) {
        cout << "Error opening output file.\n";
        return 0;
    }

    state_t *state = new state_t; 
    string line;
    
    clock_t t;
    float secs;

    while(!fileStates.eof()) {

        nodes = 0;

        getline(fileStates,line);

        if (line == "")
            continue;

        if (read_state(line.c_str(),state) <= 0) {
            printf("Error: invalid state entered.\n");
            return 0; 
        }

        print_state(output,state);

        t = clock();
        uniformCostSearch(state);
        t = clock() - t;

        secs = ((float)t)/CLOCKS_PER_SEC;

        fprintf(output,"%f %f\n", secs, nodes/secs);
    }

}