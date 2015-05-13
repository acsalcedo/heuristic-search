
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

	void initialize4x4() {

		int i;

		for(i = 0; i < 16; i++) {

			arr4x4row[i] = div(i,4).quot;
			arr4x4column[i] = i % 4;
		} 
	};

	void initialize5x5() {

		int i;

		for(i = 0; i < 25; i++) {

			arr5x5row[i] = div(i,5).quot;
			arr5x5column[i] = i % 5;
		} 
	};

	int getRow4x4(int i) {
		return arr4x4row[i];
	};

	int getColumn4x4(int i) {
		return arr4x4column[i];
	};

	int getRow5x5(int i) {
		return arr5x5row[i];
	};

	int getColumn5x5(int i) {
		return arr5x5column[i];
	};

	int getHeuristic4x4(const char **state[]) {

	 	//string goal = "B 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15";
	  	unsigned int heuristic = 0;
	  	unsigned int num = 0;
	  	unsigned int manhattan, x = 0, y;
	  	for(int i = 0; i < 16; ++i) {

	  		if (state[0][i] == "B")
		   		num = 0;
		  	else
	  			num = stoi(state[0][i],nullptr,10);
	  		
	  		y = i % 4;
	  		if (y % 4 == 0)
	  			x++;
	  		manhattan = abs(x - getRow4x4(num)) + abs(y - getColumn4x4(num));  		
	  		heuristic = heuristic + manhattan;
	  	}

	  	//cout << heuristic;
	    return heuristic;
		
	};	


    // printf("%s ", var_domain_names[0][state.vars[1]] );


    // const char **v[16] = {*var_domain_names};

//    int i;
    // for (i = 0; i < 16; i++)
    //     cout << v[0][i] << endl;
    // cout << "hola " << var_domain_names[0][1] << " :(" << endl;


    

    // Heuristics h;
    // h.initialize4x4();

    // int he = h.getHeuristic4x4(var_domain_names);

    // cout << he << endl;
	// static vector<string> split(string str, char delimiter) {
	  
	//   vector<string> internal;
	//   stringstream ss(str); // Turn the string into a stream.
	//   string tok;
	//   int i = 0;
	  
	//   while(getline(ss, tok, delimiter)) {

	//   	if (tok == "B")
	//   		i = 0;
	//   	else
	//   		i = stoi(tok,nullptr,10);

	//     internal.push_back(i);
	//   }
	  
	//   return internal;
	// };
};