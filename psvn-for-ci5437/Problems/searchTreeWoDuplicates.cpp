#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/time.h>
#include <queue>
#include <iostream>
#include "Node.cpp"

#define  MAX_LINE_LENGTH 999 

int main( int argc, char **argv ) {
// VARIABLES FOR INPUT
   char str[ MAX_LINE_LENGTH +1 ] ;
   ssize_t nchars; 
   state_t state; // state_t is defined by the PSVN API. It is the type used for individual states.

// VARIABLES FOR ITERATING THROUGH state's SUCCESSORS
   state_t child;
   ruleid_iterator_t iter; // ruleid_terator_t is the type defined by the PSVN API successor/predecessor iterators.
   int ruleid ; // an iterator returns a number identifying a rule
   int childCount = 0;
    
   std::queue<state_t> queue;
   std::queue<int> queue_h;
// READ A LINE OF INPUT FROM stdin
   //printf("Please enter a state followed by ENTER: ");
   //if ( fgets(str, sizeof str, stdin) == NULL ) {
     // printf("Error: empty input line.\n");
     // return 0; 
//   }

// CONVERT THE STRING TO A STATE
   //nchars = read_state( str, &state );
   //if (nchars <= 0) {
   //   printf("Error: invalid state entered.\n");
   //   return 0; 
   //}
   first_goal_state(&state,&ruleid);
   
   printf("The state you entered is: ");
   print_state(stdout, &state);
   printf("\n");
   int stateNumber = 0;
   float branchFactor;
   //Node *root = Node::makeRoot(state);
   int hist = init_history;

   queue.push(state);
   queue_h.push(hist);
   int depth = 0; 
   int i, child_hist;

   while (!queue.empty()) {

      stateNumber = queue.size();
      childCount = 0;
      
      // Para cada nodo del nivel actual
      for (i=0; i<stateNumber; i++) {

         state_t newNode = queue.front();
         hist = queue_h.front();
         queue.pop();
         queue_h.pop();
         init_fwd_iter(&iter, &newNode);
         
         while((ruleid = next_ruleid(&iter)) >= 0) {
            
                  
            if (!fwd_rule_valid_for_history(hist,ruleid))
               //std::cout << "Hist : " << fwd_rule_valid_for_history(hist,ruleid) << "\n";
              continue;
            
            //hist = childHistory;
            apply_fwd_rule(ruleid, &newNode, &child);
            ++childCount;
         //printf("child %d. ",childCount);
         //print_state( stdout, &child );

         //printf("  %s (cost %d), goal=%d\n",get_fwd_rule_label(ruleid),get_fwd_rule_cost(ruleid),is_goal(&child));
          
         //Node *newChild = newNode->makeNode(child,get_fwd_rule_label(ruleid));
            queue.push(child);
            queue_h.push(next_fwd_history(hist,ruleid));
         }  
      }  
      
      // Se imprimen los valores del numero de nodos, el nivel y el factor de ramificacion
      branchFactor = (float) childCount/stateNumber;
      std::cout<< "depth " << depth << ": " << stateNumber << " " << branchFactor << "\n";
      depth++;

      // Si no tiene hijos
      if (childCount == 0) {
        printf("Your state has no children.\n");
      }   
   }
   return 0;
   
} // end main
