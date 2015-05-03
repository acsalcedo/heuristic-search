
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/time.h>
#include <queue>
#include <iostream>
#include <string> 

using namespace std;

class Node {

public:
   state_t state;
   Node *parent;
   string action;
   unsigned cost;
   int depth;
   
   Node(state_t s, Node *p, string a, unsigned c, int d) : 
      state(s), parent(p), action(a), cost(c), depth(d) {};
      
   Node *makeNode(state_t s, string a) {   
      return new Node(s,this,a,this->cost,depth+1); // TODO g-cost + costo de funcion 
   };
   
   void extractPath(vector<string> &reversedPath) {
    
      Node *node = this;
      while (node != nullptr && node->parent != nullptr) {
      
         reversedPath.push_back(node->action);
         node = node->parent;
      }
   };
   
   static Node *makeRoot(state_t s) {
   
      return new Node(s,nullptr,"",0,0);
   };
   
   
};