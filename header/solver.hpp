#ifndef SOLVER_HPP
#define SOLVER_HPP
#include <iostream>
#include <cmath>
#include <map>
#include "graph.hpp"
#include "visitedstates.hpp"
#include "node.hpp"
#include "tunnel.hpp"
#include <vector>

using namespace std;

class Solver {
    private:
    public:
        Solver();
        //Prints out results for number of expanded nodes, max queue size and goal depth
        void printsolutionresults(int nodes, int maxpqsize, int goaldepth);
        /*
        //Performs uniform cost on the graph. Returns true if solution is found. Returns false if answer was not found
        bool uniformcost(Graph* graph, Visitedstates* visited);
        //Performs A* with a given heurisitc on the graph. Returns true if solution is found. Returns false if answer was not found
        bool astar(Graph* graph, Visitedstates* visited, string heuristic);*/
        //Looks for Nodes that can be reached from a blank moving in a given direction
        vector<Node*> digger(int blank, Node* temp, int direction);
        //Performs algorithm based on designated heuristic
        bool algorithm(Graph* graph, Visitedstates* visited, int heuristic);
        //Prints solution if found
        void printsolution(Node* goalnode);
};

#endif