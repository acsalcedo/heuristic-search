
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

public:
	
	Heuristics() {};

	void initialize(int problem){

		assert(problem == 4 || problem == 5);
		int i;

		if (problem == 4)  {

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
	};

	int getRow(int problem, int pos) {

		assert(problem == 4 || problem == 5);

		if (problem == 4)
			return arr4x4row[pos];
		else
			return arr5x5row[pos];
	};

	int getColumn(int problem, int pos) {

		assert(problem == 4 || problem == 5);

		if (problem == 4)
			return arr4x4column[pos];
		else
			return arr5x5column[pos];
	};

	unsigned int getHeuristicNpuzzle(int problem, var_t *state) {
		
		assert(problem == 4 || problem == 5);

		int heuristic = 0;
	  	int num = 0;
	  	int manhattan, x = -1, y;
	  	
	  	for(int i = 0; i < problem*problem; ++i) {

	  		num = (int) state[i];

	  		y = i % problem;
	  		if (y % problem == 0)
	  			x++;
	  		
	  		if (num == 0)
	  			continue;

	 		manhattan = abs(x - getRow(problem,num)) + abs(y - getColumn(problem,num));  		
	  		heuristic = heuristic + manhattan;
	  	}
	    return (unsigned int) heuristic;
	};	



};