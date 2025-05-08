#ifndef GRAPH_HPP
#define GRAPH_HPP
#include <iostream>
#include <cmath>
#include "node.hpp"
#include "tunnel.hpp"
#include <vector>

using namespace std;

class Graph {
    private:
        Node initial;
        Node goal;
        int puzzlesize;
        int numsoldiers;
        int numblanks;
    public:
        Graph();
        Graph(int size, int soldier, int blanks);
        //Set the initial state with a initial tunnel vector
        void setinitialstate(vector<int> initial);
        //Set goal state with goal tunnel vector
        void setgoalstate(vector<int> goal);
        //Return the initial node of the graph
        Node* getinitial();
        //Return the goal node of the graph
        Node* getgoal();
        //Add new node to the graph based on move and blank value
        Node* addnode(int blankval, Node* node, int move);
        //Add new node using given blank index, previous node, x and y
        Node* addnode2(int blankval, Node* node, Graph* graph, int x, int y, int move);
        int getblanks();

};

#endif