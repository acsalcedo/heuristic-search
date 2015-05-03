
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
   int childCount;
    
   std::queue<Node*> queue;

// READ A LINE OF INPUT FROM stdin
   printf("Please enter a state followed by ENTER: ");
   if ( fgets(str, sizeof str, stdin) == NULL ) {
      printf("Error: empty input line.\n");
      return 0; 
   }

// CONVERT THE STRING TO A STATE
   nchars = read_state( str, &state );
   if (nchars <= 0) {
      printf("Error: invalid state entered.\n");
      return 0; 
   }
   
   int depth = 0;
   depth++;
   printf("The state you entered is: ");
   print_state(stdout, &state);
   printf("\n");
   int stateNumber = 0;
   
   Node *root = Node::makeRoot(state);
   queue.push(root);
    
   while (!queue.empty() && depth < 4) {
      childCount = 0;
      Node *newNode = queue.front();

      queue.pop();
      init_fwd_iter(&iter, &(newNode->state));
       
      while( (ruleid = next_ruleid(&iter)) >= 0) {

         apply_fwd_rule(ruleid, &(newNode->state), &child);
         ++childCount;
         printf("child %d. ",childCount);
         print_state( stdout, &child );

         printf("  %s (cost %d), goal=%d\n",get_fwd_rule_label(ruleid),get_fwd_rule_cost(ruleid),is_goal(&child));
             
         stateNumber++;
         Node *newChild = newNode->makeNode(child,get_fwd_rule_label(ruleid));
         queue.push(newChild);
      }
      
      std::cout<< "Number of states in depth " << depth << ": " << stateNumber << "\n"; 
      depth++;
      stateNumber = 0;
      
      if (childCount == 0) {
        printf("Your state has no children.\n");
      }   
   }
   return 0;
   
} // end main
