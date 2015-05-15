
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/time.h>
#include <queue>
#include <iostream>
#include <string> 
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

class Heuristics {

	int arr4x4row[16];
	int arr4x4column[16];
	int arr5x5row[25];
	int arr5x5column[25];
	state_map_t *map1;
	state_map_t *map2;
	state_map_t *map3;
	abstraction_t *abs1;
	abstraction_t *abs2;
	abstraction_t *abs3;
	char * problem;
	bool manhattan = false;
	int size;

public:
	
	Heuristics() {};

	int initialize(char **argv){

	    if (strcmp(argv[4],"manhattan") != 0) {
	        
	        FILE *file;

	        file = fopen("abs1.state_map","r");
	        
	        if (file == nullptr) {
	            cout << "Error opening map file 1.\n";
	            return 0;
	        }

	        map1 = read_state_map(file);
	        fclose(file);
	        
	        abs1 = read_abstraction_from_file("abs1.abst");
	      
	        if (abs1 == nullptr) {
	            cout << "Error opening abstraction.\n";
	            return 0;
	        }

	        if (strcmp(argv[2],"npuzzle") == 0 || strcmp(argv[2],"rubiks") == 0) {
	         
	            file = fopen("abs2.state_map","r");
	   
	            if (file == nullptr) {
	                cout << "Error opening map file 2.\n";
	                return 0;
	            }

	            map2 = read_state_map(file);
	            fclose(file);

	            abs2 = read_abstraction_from_file("abs2.abst");

	            if (abs2 == nullptr) {
	                cout << "Error opening abstraction 2.\n";
	                return 0;
	            }

	            if (strcmp(argv[2],"npuzzle") == 0) {

		            file = fopen("abs3.state_map","r");
		            
		            if (file == nullptr) {
		                cout << "Error opening map file 3.\n";
		                return 0;
		            }
		            
		            map3 = read_state_map(file);
		            fclose(file);

		            abs3 = read_abstraction_from_file("abs3.abst");
		 
		            if (abs3 == nullptr) {
		                cout << "Error opening abstraction 3.\n";
		                return 0;
		            }
	        	}
	        }

	    } else {
	
			int i;
			manhattan = true;

			if (size == 4)  {

				for(i = 0; i < 16; i++) {

					arr4x4row[i] = div(i,4).quot;
					arr4x4column[i] = i % 4;
				}
				
			} else {

				for(i = 0; i < 25; i++) {

					arr5x5row[i] = div(i,5).quot;
					arr5x5column[i] = i % 5;
				} 
			} 			 
	    }

	    problem = argv[2];
	    size = atoi(argv[3]);
	    return 1;
	};

	void destroy() {

		if (!manhattan) {
			destroy_state_map(map1);

			if (strcmp(problem,"npuzzle")) {
				
				destroy_state_map(map2);
				destroy_state_map(map3);
			
			} else if (strcmp(problem,"rubiks")) {
				destroy_state_map(map2);
			} 
		}
	};

	int getRow(int pos) {

		if (size == 4)
			return arr4x4row[pos];
		else
			return arr5x5row[pos];
	};

	int getColumn(int pos) {

		if (size == 4)
			return arr4x4column[pos];
		else
			return arr5x5column[pos];
	};

	int getHeuristicNpuzzle(state_t *state) {
		
		int heuristic = 0;
		
		if (manhattan) {

			var_t *arr = state->vars;;
		
		  	int num = 0;
		  	int manhattan, x = -1, y;
		  	
		  	for(int i = 0; i < size*size; ++i) {

		  		num = (int) arr[i];

		  		y = i % size;
		  		if (y % size == 0)
		  			x++;
		  		
		  		if (num == 0)
		  			continue;

		 		manhattan = abs(x - getRow(num)) + abs(y - getColumn(num));  		
		  		heuristic = heuristic + manhattan;
		  	}

		    return heuristic;
		
		} else {

			state_t *stateAbst = new state_t;
        
	        abstract_state(abs1, state, stateAbst);
	        heuristic = *state_map_get(map1,stateAbst);
	        
	        abstract_state(abs2, state, stateAbst);
	        heuristic += *state_map_get(map2,stateAbst);

	        abstract_state(abs3, state, stateAbst);
	        heuristic += *state_map_get(map3,stateAbst);

	        free(stateAbst);
    
    		return heuristic;
		}
	};	

	int getHeuristicHanoi(state_t *state) {
		
		state_t *stateAbst = new state_t;
    
        abstract_state(abs1, state, stateAbst);
        int heuristic = *state_map_get(map1,stateAbst);

        free(stateAbst);

		return heuristic;
	};

	int getHeuristicTopspin(state_t *state) {
		return 0;
	};

	int getHeuristicRubiks(state_t *state) {
		
		state_t *stateAbst = new state_t;
    
        abstract_state(abs1, state, stateAbst);
        int heuristic1 = *state_map_get(map1,stateAbst);
        
        abstract_state(abs2, state, stateAbst);
        int heuristic2 = *state_map_get(map2,stateAbst);

        free(stateAbst);

		return max(heuristic1, heuristic2);
	};

	int getHeuristic(state_t *state) {

		if (strcmp(problem,"npuzzle") == 0) {
			return getHeuristicNpuzzle(state);

		} else if (strcmp(problem,"hanoi") == 0) {
			return getHeuristicHanoi(state);
		
		} else if (strcmp(problem,"topspin") == 0) {
			return getHeuristicTopspin(state);
		
		} else if (strcmp(problem,"rubiks") == 0) {
			return getHeuristicRubiks(state);
		}

		return -1;
	};
};