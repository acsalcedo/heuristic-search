#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/time.h>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <limits>

#define  MAX_LINE_LENGTH 999 

using namespace std;

void breadthFirstSearch (state_t *state) {

    state_t currentState;// = new state_t;
    state_t child;// = new state_t;
    ruleid_iterator_t iter; 
    int ruleid;

    queue<state_t> q;
    state_map_t *map = new_state_map();

    q.push(*state);
    state_map_add(map,state,0);

    int cost;

    while (!q.empty()) {

        currentState = q.front();
        q.pop();
        
        cost = *state_map_get(map,&currentState);

        if (is_goal(&currentState)) {
            cout << "Goal found with cost: " << cost << endl;
            destroy_state_map(map);
            return;
        }

        init_fwd_iter(&iter,&currentState);

        int *childCost;

        while((ruleid = next_ruleid(&iter)) >= 0 ) {

            apply_fwd_rule(ruleid,&currentState,&child);

            childCost = state_map_get(map,&child);

            if (childCost == nullptr) {   

                int newCost = cost;

                newCost += get_fwd_rule_cost(ruleid);

                state_map_add(map,&child,newCost);               
                q.push(child);
            }            
        }
    }
    destroy_state_map(map);
    cout << "No goal found.\n";
}

int main(int argc,char **argv) { 

    if (argc < 2) {
        cout << "Use: ./<exec>.bfs <nameStatesFile>\n";
        return 0;
    }

    ifstream fileStates;
    fileStates.open(argv[1]);

    if (!fileStates.is_open()) {
        cout << "Error opening file containing states.\n";
        return 0;
    }

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

        printf("Initial state: ");
        print_state(stdout,state);

        breadthFirstSearch(state);
    }
    

    //free(state);
}












