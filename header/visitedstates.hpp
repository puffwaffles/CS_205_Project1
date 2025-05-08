#ifndef VISITEDSTATES_HPP
#define VISITEDSTATES_HPP
#include <iostream>
#include <cmath>
#include <map>
#include <vector>
#include "node.hpp"
#include "tunnel.hpp"


using namespace std;

class Visitedstates {
    private:
        map<vector<int>, Node> visited; 
    public: 
    Visitedstates();
        //Adds a new state to the map of visited state
        void addstate(vector<int> v, Node node);
        //Returns map of visited states
        map<vector<int>, Node>* getvisited();
        //Checks if a state has already been visited/visited
        bool checkstate(vector<int> v);
        //Accesses the node stored for the given tunnel. Returns nulltpr if the tunnel is not stored in the map
        Node* accessstatenode(vector<int> v);
};

#endif 