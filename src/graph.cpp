#include <iostream>
#include <cmath>
#include "../header/graph.hpp"
#include "../header/node.hpp"

Graph::Graph() {
    puzzlesize = 10;
    numsoldiers = 9;
    numblanks = 4;
    initial = Node(puzzlesize, numsoldiers, numblanks);
    goal = Node(puzzlesize, numsoldiers, numblanks);
}

Graph::Graph(int size, int soldier, int blanks) {
    puzzlesize = size;
    numsoldiers = soldier;
    numblanks = blanks;
    initial = Node(puzzlesize, numsoldiers, numblanks);
    goal = Node(puzzlesize, numsoldiers, numblanks);
}

//Initializes initial state for graph
void Graph::setinitialstate(vector<int> initialstate) {
    //Establish puzzle size, number of soldiers, and number of blanks for tunnel in initial state
    *(initial.gettunnel()) = Tunnel(puzzlesize, numsoldiers, numblanks);
    //Get the tunnel of the initial state and set the tunnel vector to copy the initial state vector
    (initial.gettunnel()) -> copytunnel(initialstate);
}

//Initializes goal state for graph
void Graph::setgoalstate(vector<int> goalstate) {
    //Establish puzzle size, number of soldiers, and number of blanks for tunnel in goal state
    *(goal.gettunnel()) = Tunnel(puzzlesize, numsoldiers, numblanks);
    //Get the tunnel of the goal state and set the tunnel vector to copy the goal state vector
    (goal.gettunnel()) -> copytunnel(goalstate);
}

Node* Graph::getinitial() {
    //Return pointer to initial node so contents can be changed
    return &initial;
}

Node* Graph::getgoal() {
    //Return pointer to goal node so contents can be changed
    return &goal;
}

//Modified version of original addnode that supports the digger function in solver class
//This one uses swap directly since digger function already determines if swap is viable
Node* Graph::addnode2(int blankval, Node* node, Graph* graph, int x, int y, int move) {
    //Create new successor node
    Node* succ = nullptr;
    //Create a new node for successor
    succ = new Node(puzzlesize, numsoldiers, numblanks);
    //Set successor's previous node to node
    succ -> setprev(node);
    //Copy the previous node's tunnel
    succ -> gettunnel() -> copytunnel(node-> gettunnel()-> gettunnelvect());
    succ -> gettunnel() -> copyblank(node-> gettunnel()-> getblanksvec());
    int newloc = node-> gettunnel()-> getblanksvec().at(blankval);
    succ -> gettunnel() -> swap(blankval, x, y);
    //We do not want to create another copy of an already visited node
    if (node-> getprev() != nullptr && (node-> getprev()-> gettunnel() -> gettunnelvect() == succ-> gettunnel() -> gettunnelvect())) {
        succ-> setprev(nullptr);
        succ = nullptr;
    }
    //Otherwise, proceed to making the successor node
    else {
        //Set up gcost
        succ -> setgcost((succ -> getprev()) -> getgcost() + 1);
    }
    return succ;
}

//returns blanks for graph
int Graph::getblanks() {
    return numblanks;
}