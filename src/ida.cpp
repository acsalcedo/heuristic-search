#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/time.h>
#include <iostream>
#include <fstream>
#include <string>
#include "heuristics.hpp"
#include <limits>
#include <time.h>

#define  MAX_LINE_LENGTH 999 
Heuristics h;

unsigned long int nodes = 0;

using namespace std;

pair<state_t*,int> boundDFS(state_t *state, int cost, int bound, int hist) {

    int f = cost + h.getHeuristic(state);
    
    if (f > bound)
        return make_pair(nullptr,f);

    if (is_goal(state)) 
        return make_pair(state,cost);
    
    int ruleid;
    ruleid_iterator_t iter;

    int t = INT_MAX;
    
    pair<state_t*,int> n;

    state_t *child = new state_t;

    init_fwd_iter(&iter,state);
         
    nodes++;
    
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

    if (argc < 6) {
        cout << "Use: ./<exec>.ida <nameStatesFile> <problem> <size> <typeHeuristic> <outputFile>\n";
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

    FILE *output;
    output = fopen(argv[5],"w");
    
    if (output == nullptr) {
        cout << "Error opening output file.\n";
        return 0;
    }

    h.initialize(argv);

    state_t *state = new state_t;

    string line;

    clock_t t;

    while(!fileStates.eof()) {

        nodes = 0;

        getline(fileStates,line);

        if (line == "")
            continue;

        if (read_state(line.c_str(),state) <= 0) {
            printf("Error: invalid state entered.\n");
            return 0; 
        }

        int bound = h.getHeuristic(state);
        float secs, nodesSecs;

        pair<state_t*,int> p;

        t = clock();
        
        while (true) {
            
            p = boundDFS(state,0,bound,init_history);
            
            if (p.first != nullptr)
                break;

            bound = p.second;            
        }
        
        t = clock() - t;
        
        print_state(output,state);
        secs = ((float)t)/CLOCKS_PER_SEC;

        if (secs == 0)
            nodesSecs = 0;
        else
            nodesSecs = nodes/secs;

        fprintf(output, ": - %i %lu %f %f \n",p.second,nodes,secs,nodesSecs);
     }

    //h.destroy();
    fileStates.close(); 
    fclose(output);
}