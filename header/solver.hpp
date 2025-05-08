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
        
        //Looks for Nodes that can be reached from a blank moving in a given direction
        vector<Node*> digger(int blank, Node* temp, Graph* graph, int direction);
        //Performs algorithm based on designated heuristic. This one is outdated since it does not consider switching directions
        //bool algorithm(Graph* graph, Visitedstates* visited, int heuristic);
        
        //Performs algorithm based on designated heuristic. This one employs directional switching
        bool algorithm2(Graph* graph, Visitedstates* visited, int heuristic);
        //Prints solution if found
        void printsolution(Node* goalnode);
};

#endif