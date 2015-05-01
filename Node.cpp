
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/time.h>
#include <queue>
#include <iostream>
#include <string>

class Node {

public:
   state_t state;
   Node parent;
   String action;
   unsigned g-cost = 0;
   int depth;
   
   Node(state_t s, Node p, String a, unsigned c, int d) : 
      state(s), parent(p), action(a), g-cost(c), depth(d) {};
      
   Node makeNode(state_t s, String a) {   
      return new Node(s,this,a,g-cost,depth++); // TODO g-cost + costo de funcion 
   };
   
   void extractPath(vector<String> &reversedPath) {
    
      Node node = this;
      while (node != null && node.parent != null) {
      
         reversedPath.push_back(node.action);
         node = node.parent;
      }
   };
   
   Node makeRoot(state_t s) {
   
      return new Node(s,null,"",0);
   };
   
   
};


void Node::