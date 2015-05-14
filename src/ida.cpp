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
state_map_t *map1, *map2, *map3;

using namespace std;


pair<state_t*,int> boundDFS(state_t *state, int cost, int bound, abstraction_t *abs1, abstraction_t *abs2, abstraction_t *abs3, int hist) {

    state_t *child = new state_t;
    state_t *stateAbst = new state_t;
    
    int ruleid;
    ruleid_iterator_t iter;
    int childCost = 0;

    abstract_state(abs1, state, stateAbst);
    int f = cost + *state_map_get(map1,stateAbst);
    
    abstract_state(abs2, state, stateAbst);
    f += *state_map_get(map2,stateAbst);

    abstract_state(abs3, state, stateAbst);
    f += *state_map_get(map3,stateAbst);
    
    /*(int) h.getHeuristicNpuzzle(4,state->vars)*/

    free(stateAbst);

    if (f > bound)
        return make_pair(nullptr,f);

    if (is_goal(state)) {
        cout << "cost: " << cost << endl;   
        return make_pair(state,cost);
    }

    int t = INT_MAX;
    pair<state_t*,int> n;

    init_fwd_iter(&iter,state);
         
    while((ruleid = next_ruleid(&iter)) >= 0) {
    
        apply_fwd_rule(ruleid,state,child);

        if (!fwd_rule_valid_for_history(hist,ruleid))
            continue;

        int newCost = cost+get_fwd_rule_cost(ruleid);

        n = boundDFS(child,newCost,bound,abs1,abs2,abs3,next_fwd_history(hist,ruleid));
        
        if (n.first != nullptr) {             
            return n;
       }

     t = min(t,n.second);

    }

    free(child);
    return make_pair(nullptr,t);   
}


int main(int argc,char **argv) {

    state_t *state = new state_t;

    FILE *file;
    file = fopen("abs1.state_map","r");
    
    if (file == nullptr) {
        cout << "Error opening map file 1.\n";
        return 0;
    }
    
    map1 = read_state_map(file);
    fclose(file);
    file = fopen("abs2.state_map","r");
    
    if (file == nullptr) {
        cout << "Error opening map file 2.\n";
        return 0;
    }

    map2 = read_state_map(file);
    fclose(file);
    file = fopen("abs3.state_map","r");
    
    if (file == nullptr) {
        cout << "Error opening map file 3.\n";
        return 0;
    }
    
    map3 = read_state_map(file);
    fclose(file);
    
    abstraction_t *abs1 = read_abstraction_from_file("abs1.abst");
  
    if (abs1 == nullptr) {
        cout << "Error opening abstraction.\n";
        return 0;
    }

    abstraction_t *abs2 = read_abstraction_from_file("abs2.abst");
    abstraction_t *abs3 = read_abstraction_from_file("abs3.abst");

    h.initialize(4);
    
    string line;
    ifstream fileStates;
    fileStates.open ("states.txt");

    while(!fileStates.eof()) {

        getline(fileStates,line);

        if (read_state(line.c_str(),state) <= 0) {
            printf("Error: invalid state entered.\n");
            return 0; 
        }

        printf("The state you entered is: ");
        print_state(stdout,state);
        printf("\n");
    
        state_t *stateAbst = new state_t;

        abstract_state(abs1, state, stateAbst);
        int bound = *state_map_get(map1,stateAbst);
        
        abstract_state(abs2, state, stateAbst);
        bound += *state_map_get(map2,stateAbst);

        abstract_state(abs3, state, stateAbst);
        bound += *state_map_get(map3,stateAbst);

        free(stateAbst);
    
        pair<state_t*,int> p;// = new pair;

        while (true) {
            
            p = boundDFS(state,0,bound,abs1,abs2,abs3,init_history);
            
            if (p.first != nullptr) {
                cout << "Goal found with cost: " << p.second << endl;
                break;
            }   
            bound = p.second;            
        }
    }
    
    fileStates.close();

    destroy_abstraction(abs1);
    destroy_abstraction(abs2);
    destroy_abstraction(abs3);

    





    //h.getHeuristicNpuzzle(4,state->vars);


    //free(p);

}