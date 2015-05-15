#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/time.h>
#include <iostream>
#include <limits>
#include <fstream>
#include <string>
#include <time.h>

#define  MAX_LINE_LENGTH 999 

FILE *output;
unsigned long int nodes = 0;

using namespace std;

pair<state_t*, int> boundedDfs(state_t state, int bound, int cost, int hist) {

    int ruleid;
    state_t child;
    ruleid_iterator_t iter;
    
    if (cost > bound)
        return make_pair(nullptr,cost);

    if (is_goal(&state))
        return make_pair(&state,cost);

    int t = INT_MAX;

    init_fwd_iter(&iter,&state);

    nodes++;
         
    while((ruleid = next_ruleid(&iter)) >= 0) {
        apply_fwd_rule(ruleid,&state, &child);

        if (!fwd_rule_valid_for_history(hist,ruleid))
            continue;

        int newCost = cost+get_fwd_rule_cost(ruleid);

        pair<state_t*, int> n = boundedDfs(child,bound,newCost,next_fwd_history(hist,ruleid));
        
        if (n.first != nullptr) 
            return make_pair(n.first, n.second);

        t = min(t,n.second);
    }
    return make_pair(nullptr,t);       
}

int main(int argc,char **argv) {

    if (argc < 3) {
        cout << "Use: ./<exec>.dfucs <nameStatesFile> <outputFile>\n";
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
    int bound;

    while(!fileStates.eof()) {

        nodes = 0;

        getline(fileStates,line);

        if (line == "")
            continue;

        if (read_state(line.c_str(),state) <= 0) {
            printf("Error: invalid state entered.\n");
            return 0; 
        }

        bound = 0;
        pair<state_t*, int> p;

        t = clock();

        while (true) {

           p = boundedDfs(*state,bound,0,init_history);

           if (p.first != nullptr)
               break;

           bound = p.second;           
        }

        t = clock() - t;

        print_state(output,state);
        secs = ((float)t)/CLOCKS_PER_SEC;
        fprintf(output, ": - %i %lu %f %f \n",p.second,nodes,secs,nodes/secs);
    }
}