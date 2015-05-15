#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/time.h>
#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include "heuristics.hpp"
#include <limits>

#define  MAX_LINE_LENGTH 999 
Heuristics h;

using namespace std;


pair<state_t*,int> boundDFS(state_t *state, int cost, int bound, int hist) {

    state_t *child = new state_t;
    state_t *stateAbst = new state_t;
    
    int ruleid;
    ruleid_iterator_t iter;

    int f = cost + h.getHeuristic(state);
    
    if (f > bound)
        return make_pair(nullptr,f);

    if (is_goal(state))
        return make_pair(state,cost);
    
    int t = INT_MAX;
    pair<state_t*,int> n;

    init_fwd_iter(&iter,state);
         
    while((ruleid = next_ruleid(&iter)) >= 0) {
    
        apply_fwd_rule(ruleid,state,child);

        if (!fwd_rule_valid_for_history(hist,ruleid))
            continue;

        int newCost = cost+get_fwd_rule_cost(ruleid);

        n = boundDFS(child,newCost,bound,next_fwd_history(hist,ruleid));
        
        if (n.first != nullptr) {             
            return n;
       }

     t = min(t,n.second);
    }

    free(child);
    return make_pair(nullptr,t);   
}


int main(int argc,char **argv) {

    if (argc < 5 ) {
        cout << "Use: ./<exec> <nameStatesFile> <problem> <size> <typeHeuristic>\n";
        cout << "problem: npuzzle / rubiks / topspin / hanoi\n";
        cout << "typeHeuristic:\n";
        cout << "if problem to solve is n-puzzle: 0 = manhattan, 1 = pdb.\n";
        cout << "if problem to solve is rubik's cube: 0 = corner, 1 = edge.\n";
        cout << "if problem is hanoi or topspin, there is no third argument.\n";
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

        if (read_state(line.c_str(),state) <= 0) {
            printf("Error: invalid state entered.\n");
            return 0; 
        }

        printf("The state you entered is: ");
        print_state(stdout,state);
        printf("\n");
    
        int bound = h.getHeuristic(state);

        pair<state_t*,int> p;

        while (true) {
            
            p = boundDFS(state,0,bound,init_history);
            
            if (p.first != nullptr) {
                cout << "Goal found with cost: " << p.second << endl;
                break;
            }   
            bound = p.second;            
        }
    }
    fileStates.close(); 
}