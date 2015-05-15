#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/time.h>
#include <queue>
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <algorithm> 
#include <time.h>

#define  MAX_LINE_LENGTH 999 

FILE *output;
unsigned long int nodes = 0;

using namespace std;

pair<state_t*,unsigned long int> boundeddfs(state_t state, unsigned long int bound,unsigned long int depth, int hist) {
   
    int ruleid;
    state_t child;
    ruleid_iterator_t iter;

    if (depth > bound) 
        return make_pair(nullptr,depth);

    if (is_goal(&state)) {
        return make_pair(&state,depth);
    }

    init_fwd_iter(&iter,&state);

    nodes++;

    while((ruleid = next_ruleid(&iter)) >= 0) {

        apply_fwd_rule(ruleid,&state,&child);

        if (!fwd_rule_valid_for_history(hist,ruleid))
            continue;

        pair<state_t*,unsigned long int> n = boundeddfs(child,bound,depth+1,next_fwd_history(hist,ruleid));

        if (n.first != nullptr)
            return make_pair(n.first,n.second);
    }  
    return make_pair(nullptr,depth);
}

int main( int argc, char **argv ) {

    if (argc < 3) {
        cout << "Use: ./<exec>.dfid <nameStatesFile> <outputFile>\n";
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
    float secs, nodesSecs;

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
        
        unsigned long int bound = 0;

        pair<state_t*,unsigned long int> n;
        
        while (true) {
          
            n = boundeddfs(*state,bound,0,init_history);

            if (n.first != nullptr)
                break;

            bound++;
        }
        
        t = clock() - t;
    
        fprintf(output, ": - %lu %lu ", bound, nodes);

        secs = ((float)t)/CLOCKS_PER_SEC;

        if (secs == 0)
            nodesSecs = 0;
        else
            nodesSecs = nodes/secs;

        fprintf(output,"%f %f\n",secs,nodesSecs);
    }


} 