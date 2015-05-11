#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/time.h>
#include <iostream>
#include "priority_queue.hpp"

using namespace std;

int main( int argc, char **argv ) {
// VARIABLES FOR INPUT
//    char str[ MAX_LINE_LENGTH +1 ] ;
//    ssize_t nchars; 
//    state_t state; // state_t is defined by the PSVN API. It is the type used for individual states.

// // VARIABLES FOR ITERATING THROUGH state's SUCCESSORS
//    state_t child;
//    ruleid_iterator_t iter; // ruleid_terator_t is the type defined by the PSVN API successor/predecessor iterators.
//    int ruleid ; // an iterator returns a number identifying a rule
//    int childCount = 0;
    
//    std::queue<state_t> queue;
//    std::queue<int> queue_h;
// // READ A LINE OF INPUT FROM stdin
//    printf("Please enter a state followed by ENTER: ");
//    if ( fgets(str, sizeof str, stdin) == NULL ) {
//      printf("Error: empty input line.\n");
//      return 0; 
//   }

// //CONVERT THE STRING TO A STATE
//    nchars = read_state( str, &state );
//    if (nchars <= 0) {
//      printf("Error: invalid state entered.\n");
//      return 0; 
//    }
//    first_goal_state(&state,&ruleid);
   
//    printf("The state you entered is: ");
//    print_state(stdout, &state);
//    printf("\n");
//    int stateNumber = 0;
//    float branchFactor;

	PriorityQueue<string> pq = PriorityQueue<string>();

	pq.Add(4,4,"hola1");
	pq.Add(3,3,"hola2");


	//cout << pq.buckem_stacks[0][1] << "\n";
	pq.Modify(3,3,0,"hola3");

	cout << pq.Top() << "\n";




}