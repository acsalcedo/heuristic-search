
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
   int color; // -1 gray, 0 white, 1 black
   
   Node(state_t s, Node *p, string a, unsigned c, int d, int cl) : 
      state(s), parent(p), action(a), cost(c), depth(d), color(cl) {};
      
   Node *makeNode(state_t s, string a) {   
      return new Node(s,this,a,this->cost,depth+1, 0); // TODO g-cost + costo de funcion 
   };
   
   void extractPath(vector<string> &reversedPath) {
    
      Node *node = this;
      while (node != NULL && node->parent != NULL) {
      
         reversedPath.push_back(node->action);
         node = node->parent;
      }
   };
   
   static Node *makeRoot(state_t s) {
   
      return new Node(s,NULL,"",0,0,0);
   };
   
   void setColor(int color) {
      this->color = color;
   };

   int getColor() {
      return this->color;
   };

   state_t getState() {
      return this->state;
   };

   unsigned getCost() {
      return this->cost;
   };

   void setCost(unsigned c) {
      this->cost = c;
   };
};

class CompareCosts {
public:
   bool operator()(Node* n1, Node* n2) {
      if (n1->cost < n2->cost)
         return false;
      return true;
   };
};