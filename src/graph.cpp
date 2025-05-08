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

void Graph::setinitialstate(vector<int> initialstate) {
    *(initial.gettunnel()) = Tunnel(puzzlesize, numsoldiers, numblanks);
    /*(initial.gettunnel()) -> setsize(puzzlesize);
    cout << "set size" << endl;
    (initial.gettunnel()) -> setsoldiers(numsoldiers);
    cout << "set soldiers" << endl;
    (initial.gettunnel()) -> setblanks(numblanks);
    cout << "set blanks" << endl;*/
    //Get the tunnel of the initial state and set the tunnel vector to copy the initial state vector
    (initial.gettunnel()) -> copytunnel(initialstate);
}

void Graph::setgoalstate(vector<int> goalstate) {
    //Get the tunnel of the goal state and set the tunnel vector to copy the goal state vector
    (goal.gettunnel()) -> copytunnel(goalstate);
    (goal.gettunnel()) -> setsize(puzzlesize);
    (goal.gettunnel()) -> setsoldiers(numsoldiers);
    (goal.gettunnel()) -> setblanks(numblanks);
}

Node* Graph::getinitial() {
    //Return pointer to initial node so contents can be changed
    return &initial;
}

Node* Graph::getgoal() {
    //Return pointer to goal node so contents can be changed
    return &goal;
}

Node* Graph::addnode(int blankval, Node* node, int move) {
    //Create new successor node
    Node* succ = nullptr;
    //cout << "In addnode" << endl;
    //If the successor node can be accessed as a move swap
    if ((node-> gettunnel()) -> canswap(blankval, move)) {
        //cout << "canswap function is fine" << endl;
        //Create a new node for successor
        succ = new Node(puzzlesize, numsoldiers, numblanks);
        //Set successor's previous node to node
        succ -> setprev(node);
        //Copy the previous node's tunnel
        succ -> gettunnel() -> copytunnel(node-> gettunnel()-> gettunnelvect());
        //cout << "copied tunnel" << endl;
        //cout << "blankval: " << blankval << endl;
        //Perform the swap based on the given node
        succ -> gettunnel() -> swapsoldier(blankval, move);
        //cout << "swapsoldier function is fine" << endl;
        //Check if the swapped node isn't the previous node of node
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
    }
    //cout << "Created node" << endl;
    //Set up the corresponding successor node pointer for node
    node-> setdirs(succ, move - 1);
    return succ;
}

int Graph::getblanks() {
    return numblanks;
}