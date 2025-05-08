#include <iostream>
#include <cmath>
#include <map>
#include <queue>
#include "../header/solver.hpp"
#include "../header/graph.hpp"
#include "../header/visitedstates.hpp"
#include "../header/node.hpp"
#include "../header/tunnel.hpp"
#include <vector>
#include <stack>

//Comparison class to compare nodes by accumulated cost
class Comparison {
    public:
        bool operator()(Node* n1, Node* n2) {
            bool comparison = n1-> gettotalcost() > n2-> gettotalcost();
            return comparison;
        }
};

Solver::Solver() {

}

void Solver::printsolutionresults(int nodes, int maxpqsize, int goaldepth) {
    cout << "To solve this problem the search algorithm expanded a total of " << nodes << " nodes." << endl;
    cout << "The maximum number of nodes in the queue at any one time: " << maxpqsize << "." << endl;
    cout << "The depth of the goal node was " << goaldepth << "." << endl;
}

vector<Node*> Solver::digger(int blank, Node* temp, int direction) {
    vector<Node*> succs;
    return succs;
}

bool Solver::algorithm(Graph* graph, Visitedstates* visited, int heuristic) {
    bool hassolution = false;
    //cout << "Num blanks in graph: "  << graph -> getblanks() << endl;
    //Get the initial state node of the graph
    graph-> getinitial() -> nodecostsetup(heuristic);
    Node* initial = graph-> getinitial();
    //cout << "initial blank size: " << initial -> gettunnel() -> getblanksvec().size() << endl;
    //cout << "Num blanks in initial: "  << initial -> getblanks() << endl;
    //Priority queue to hold nodes to be sorted by node cost
    priority_queue<Node*, vector<Node*>, Comparison> pq;
    //Initialize priority queue
    pq.push(initial);
    //Use temp to iterate through graph
    Node* temp;
    temp = initial;
    //Add this state to the visited map
    visited-> addstate(initial -> gettunnel()-> gettunnelvect(), *initial);
    //Use succ to keep track of successor nodes
    Node* succ = nullptr;
    //Use to keep track of expanded nodes
    int nodes = 0;
    //Used to store max priority queue size
    int maxpqsize = 0;
    //Used to store the goal node's depth
    int goaldepth = 0;
    //First time expanding state
    cout << "Expanding state" << endl;
    initial-> gettunnel()-> displaytunnel();
    cout << endl;
    while (!pq.empty()) {
        //Update maxpqsize if it exceeds the previous value
        if (pq.size() > maxpqsize) {
            maxpqsize = pq.size();
        }
         //Retrive the first node from the priority queue. This node should have the smallest cost
        temp = pq.top();
        //If nodes = 0, update nodes to 1 to account for the initial node
        if (nodes < 1) {
            nodes++;
        }
        //Check if the node is the goal solution. We break out of the loop once we find the goal node and indicate that we have a solution
        if (temp-> checkgoal()) {
            goaldepth = temp-> getgcost();
            cout << endl;
            cout << "Goal!!!" << endl;
            hassolution = true;
            printsolution(temp);
            break;
        }
        //Check if we have already encountered the node. It is possible to add cheaper duplicates
        else if ((visited-> checkstate(temp-> gettunnel()-> gettunnelvect())) && (visited-> getvisited()-> at(temp-> gettunnel()-> gettunnelvect()).gettotalcost() < (temp-> gettotalcost()))) {
            //Just pop off the node if we already expanded the cheaper version
            pq.pop();       
        }
        //Otherwise, we can print this display of the best state to expand to and find successor nodes for that state
        else {
            cout << "The best state to expand with g(n) = " << temp-> getgcost() << " and h(n) = " << temp-> gethcost() << " is" << endl;
            temp-> gettunnel()-> displaytunnel();
            cout << endl;
            cout << endl;
            /*//Just want to compare results at diamter.
            if (temp-> getgcost() > 3) {
                break;
            }*/
            //Pop that node off 
            pq.pop();
            cout << "Expanding this node..." << endl;
            //Add the successor node as one of the nodes we expanded to
            nodes++;
            //cout << "Blanks size in solver is: " << blanks.size() << endl;
            //cout << "Getting blank values is fine" << endl;
            
            //Iterate through the successor nodes of temp. First iterate through each blank
            vector<int> blanks = temp -> gettunnel() -> getblanksvec();
            for (int j = 0; j < blanks.size(); j++) {

                //Then iterate through each direction for each blank
                for (int i = 0; i < 4; i++) {
                    
                    /*if (i + 1 == 4) {
                        cout << "Checking right swap" << endl;
                    }*/
                    
                    //Create the successor node for each move i (up, down, left, right). If no such move exists or if the successor is the same state as the node's previous node, the successor node will be rendered as null
                    succ = graph-> addnode(j, temp, i + 1);
                    //cout << j << " " << i << " succ is fine" << endl;
                    
                    //Make sure succ state exists
                    if (succ != nullptr) {
                        //Set up costs for succ using gcost based on designated heuristic
                        succ-> nodecostsetup(heuristic); 
                        //Check if successor has been added to the visited map  
                        if (!(visited-> checkstate(succ-> gettunnel()-> gettunnelvect()))) {
                            //cout << "New state! " << endl;
                            //succ-> gettunnel()-> displaytunnel();
                            //cout << "g(n) = " << succ-> getgcost() << " and h(n) = " << succ-> gethcost() << " is" << endl;
                            //Add this new state to the map
                            visited-> addstate(succ -> gettunnel()-> gettunnelvect(), *succ);
                            //Add this new node to the priority queue
                            pq.push(succ);
                        }
                        else {
                            // Then check if successor's total cost is less than the same state node
                            if (visited-> getvisited()-> at(succ-> gettunnel()-> gettunnelvect()).gettotalcost() > (succ-> gettotalcost())) {
                                //Replace the more costly state with this cheaper state
                                visited-> addstate(succ -> gettunnel()-> gettunnelvect(), *succ);
                                //Add this cheaper node to the priority queue
                                pq.push(succ);
                            }
                        }
                    }
                }
            }
        }
        //Update maxpqsize if it exceeds the previous value
        if (pq.size() > maxpqsize) {
            maxpqsize = pq.size();
        } 
    }
    //If there was a solution, print these results
    printsolutionresults(nodes, maxpqsize, goaldepth);
    return hassolution;
}

void Solver::printsolution(Node* goalnode) {
    Node* temp = nullptr;
    temp = goalnode;
    stack<Node*> steps;
    while (temp != nullptr) {
        steps.push(temp);
        temp = temp-> getprev();
    }
    cout << "Solution: " << endl;
    cout << "\nOriginal problem: " << endl;
    cout << endl;
    temp = steps.top();
    temp-> gettunnel()-> displaytunnel();
    steps.pop();
    int step = 0;/*
    if (!steps.empty()) {
        temp = steps.top();
        temp-> gettunnel()-> displaytunnel();
        steps.pop();
        cout << endl;
    }*/
    while (!steps.empty()) {
        step++;
        cout << step << "." << endl;
        temp = steps.top();
        temp-> gettunnel()-> displaytunnel();
        steps.pop();
        cout << endl;
    }
}