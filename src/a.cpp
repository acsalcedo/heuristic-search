#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/time.h>
#include <iostream>
#include <fstream>
#include <string>
#include "priority_queue.hpp"
#include "heuristics.hpp"
#include <limits>

#define  MAX_LINE_LENGTH 999 
Heuristics h;

using namespace std;

void bestFirstSearch(state_t *state) {

    PriorityQueue<state_t> pq;
    pq.Add(0,0,*state);

    state_map_t *map = new_state_map();
    state_map_add(map,state,0);

    state_t currentState;
    state_t child;

    int *cost;
    int ruleid, priority, childCost;
    ruleid_iterator_t iter;

    while (!pq.Empty()) {

        priority = pq.CurrentPriority();

        currentState = pq.Top();
        pq.Pop();           

        cost = state_map_get(map,&currentState);

        if (cost == nullptr || priority <= *cost) {

            /* The state added to map is Gray */
            state_map_add(map,&currentState,priority);

            if (is_goal(&currentState)) {
                cout << "- Goal found with cost: " << priority << endl;
                destroy_state_map(map);
                return;
            }           

            init_fwd_iter(&iter,&currentState);

            while((ruleid = next_ruleid(&iter)) >= 0) {

                apply_fwd_rule(ruleid,&currentState,&child);

                if (h.getHeuristicNpuzzle(&child) < UINT_MAX) {                
                    childCost = priority + get_fwd_rule_cost(ruleid);
                    state_map_add(map,&child,childCost);
                    pq.Add(childCost,childCost,child);
                }
            }           
        }
    }
    destroy_state_map(map);
    cout << "No goal found.\n";
}

int main( int argc, char **argv ) {

    if (argc < 5 ) {
        cout << "Use: ./<exec>.a <nameStatesFile> <problem> <size> <typeHeuristic>\n";
        cout << "problem: npuzzle / rubiks / topspin / hanoi\n";
        cout << "typeHeuristic:\n";
        cout << "If problem to solve is n-puzzle: manhattan / pdb\n";
        cout << "If problem to solve is rubik's cube: corner / edge\n";
        cout << "If problem is hanoi or topspin, there is no fifth argument.\n";
        return 0;
    }
    
    ifstream fileStates;
    fileStates.open(argv[1]);

    if (!fileStates.is_open()) {
        cout << "Error opening file containing states.\n";
        return 0;
    }

    h.initialize(argv);

    state_t *state = new state_t;

    string line;

    while(!fileStates.eof()) {

        getline(fileStates,line);

        if (line == "")
            continue;

        if (read_state(line.c_str(),state) <= 0) {
            printf("Error: invalid state entered.\n");
            return 0; 
        }

        cout << "Initial state: ";
        print_state(stdout,state);
        
    
        int bound = h.getHeuristic(state);

        bestFirstSearch(state);
    }     

    h.destroy();
}