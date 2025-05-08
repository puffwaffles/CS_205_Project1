#ifndef MENU_HPP
#define MENU_HPP
#include <iostream>
#include <cmath>
#include "solver.hpp"
#include "graph.hpp"
#include "node.hpp"
#include "tunnel.hpp"
#include <vector>
using namespace std;

class Menu {
    private:
        Graph graph;
        Solver solver;
        Visitedstates visited;
        int puzzletype;
        int puzzlesize;
        int soldiers;
        int blanks;
        vector<int> initial;
        vector<int> goal;
        int algorithm;
    public:
        Menu();
        //Returns the graph to be generated
        Graph* getgraph();
        //Prompt user for either default puzzle or custom puzzle
        void promptpuzzletype();
        //Make default puzzle
        vector<int> makedefault();
        //Prompt user for size of the puzzle. Puzzle will be a size by size tunnel
        void promptpuzzlesize();
        //Prompt user for order of tiles in puzzle if user chooses custom puzzle
        void promptpuzzle();
        //Prompt user for algorithm to be visited
        void promptalgorithm();
        //Create puzzle based on user input and choice of puzzle type (default or custom)
        void developpuzzle();
        //Execute algorithm chosen by user
        void beginalgorithm();

};

#endif