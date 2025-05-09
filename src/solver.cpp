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
#include <fstream>
#include <chrono>

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
    ofstream f;
    f.open("info.txt", ios::app);
    f << "To solve this problem the search algorithm expanded a total of " << nodes << " nodes." << endl;
    f << "The maximum number of nodes in the queue at any one time: " << maxpqsize << "." << endl;
    f << "The depth of the goal node was " << goaldepth << "." << endl;
    f.close();
}

vector<Node*> Solver::digger(int blank, Node* temp, Graph* graph, int direction) {
    vector<int> vt = {-1, -1, -1, 0, -1, 0, -1, 8, -1, -1, 1, 2, 3, 4, 5, 6, 0, 0, 7, 9};
    vector<Node*> succs;
    //Extract location of blank in vector and vector size
    int bloc = temp-> gettunnel()-> getblanksvec().at(blank);
    int size = temp-> gettunnel()-> getsize();
    //Retrieve x and y 
    int x = bloc % size;
    int y = bloc / size;

    //Keep track of direction we will be moving 
    int dir = direction;

    //Create vector for x, y, dir, changes
    vector<int> v = {x, y, dir, 0};

    
    //Keep track of avenues we can explore
    stack<vector<int>> explore;
    explore.push(v);

    //Vectors for direction avenues. Only 2 per direction since we don't want to backtrack
    vector<int> updown = {3, 4};
    vector<int> leftright = {1, 2};

    int val = 0;

    //Condition for deadend
    bool deadend = false;
    //Iterate through different viable paths for soldiers
    while (!explore.empty()) {
        //Extract avenue as v
        v = explore.top();
        x = v.at(0);
        y = v.at(1);
        deadend = false;
        //Keep going in one direction until we can't anymore
        while (!deadend) {
            dir = v.at(2);
            switch(dir) {
                //Going up
                case 1:
                    //Blank must be on bottom row (1)
                    if (v.at(1) == 1) {
                        //Look at value above
                        val = temp-> gettunnel() -> getnum(v.at(0), v.at(1) - 1);
                        //If we find another blank go up a level
                        if (val == 0) {
                            v.at(1)--;
                        }
                        //It is a soldier or barrier
                        else {
                            //If it is a soldier, create a new node that swaps with this soldier and add it to succs vector
                            if (val > 0 && val <= temp-> gettunnel() -> getsoldiers()) {
                                succs.push_back(graph-> addnode2(blank, temp, graph, v.at(0), v.at(1) - 1, dir));
                            }
                            //We are done with going in this direction
                            explore.pop();
                            
                            //If we are still our blank, add new avenues to explore
                            //We also want to stop if we exceed 3 changes since we won't change direction more than 3 times
                            if (y != v.at(1) && v.at(3) < 3) {
                                for (int i = 0; i < updown.size(); i++) {
                                    explore.push({x, v.at(1), updown.at(i), v.at(3) + 1});
                                }
                            }
                            deadend = true;
                        }
                    }
                    //We are going out of bounds
                    else {
                        //We are done with going in this direction
                        explore.pop();
                        //If we are still our blank, add new avenues to explore
                        //We also want to stop if we exceed 3 changes since we won't change direction more than 3 times
                        if (y != v.at(1) && v.at(3) < 3) {
                            for (int i = 0; i < updown.size(); i++) {
                                explore.push({x, v.at(1), updown.at(i), v.at(3) + 1});
                            }
                        }
                        deadend = true;
                    }
                    break;
                
                //Going down
                case 2:
                    //Blank must be on top row (0)
                    if (v.at(1) == 0) {
                        //Look at value below
                        val = temp-> gettunnel() -> getnum(v.at(0), v.at(1) + 1);
                        //If we find another blank go down a level
                        if (val == 0) {
                            v.at(1)++;
                        }
                        //It is a soldier or barrier
                        else {
                            //If it is a soldier, create a new node that swaps with this soldier and add it to succs vector
                            if (val > 0 && val <= temp-> gettunnel() -> getsoldiers()) {
                                succs.push_back(graph-> addnode2(blank, temp, graph, v.at(0), v.at(1) + 1, dir));
                            }
                            //We are done with going in this direction
                            explore.pop();
                            //If we can backtrack to a blank that wasn't our blank, add new avenues to explore
                            //We also want to stop if we exceed 3 changes since we won't change direction more than 3 times
                            if (y != v.at(1) && v.at(3) < 3) {
                                for (int i = 0; i < updown.size(); i++) {
                                    explore.push({x, v.at(1), updown.at(i), v.at(3) + 1});
                                }
                            }
                            deadend = true;
                        }
                    }
                    //We are going out of bounds
                    else {
                        //We are done with going in this direction
                        explore.pop();
                        //If we are still our blank, add new avenues to explore
                        //We also want to stop if we exceed 3 changes since we won't change direction more than 3 times
                        if (y != v.at(1) && v.at(3) < 3) {
                            for (int i = 0; i < updown.size(); i++) {
                                explore.push({x, v.at(1), updown.at(i), v.at(3) + 1});
                            }
                        }
                        deadend = true;
                    }
                    break;
                
                //Going left
                case 3:
                    //Blank must be to the right of the first column (0) 
                    if (v.at(0) > 0 && v.at(0) <= temp-> gettunnel() -> getsize() - 1) {
                        //Look at value to the left
                        val = temp-> gettunnel() -> getnum(v.at(0) - 1, v.at(1));
                        //If we find another blank go left a level
                        if (val == 0) {
                            v.at(0)--;
                        }
                        //It is a soldier or barrier
                        else {
                            //If it is a soldier, create a new node that swaps with this soldier and add it to succs vector
                            if (val > 0 && val <= temp-> gettunnel() -> getsoldiers()) {
                                succs.push_back(graph-> addnode2(blank, temp, graph, v.at(0) - 1, v.at(1), dir));
                            }
                            //We are done with going in this direction
                            explore.pop();
                            
                            //If we can backtrack to a blank that wasn't our blank, add new avenues to explore
                            //We also want to stop if we exceed 3 changes since we won't change direction more than 3 times
                            if (x != v.at(0) && v.at(3) < 3) {
                                for (int i = 0; i < leftright.size(); i++) {
                                    explore.push({v.at(0), y, leftright.at(i), v.at(3) + 1});
                                }
                            }
                            deadend = true;
                        }
                    }
                    //We are going out of bounds
                    else {
                        //We are done with going in this direction
                        explore.pop();
                        //If we are still our blank, add new avenues to explore
                        //We also want to stop if we exceed 3 changes since we won't change direction more than 3 times
                        if (x != v.at(0) && v.at(3) < 3) {
                            for (int i = 0; i < leftright.size(); i++) {
                                explore.push({v.at(0), y, leftright.at(i), v.at(3) + 1});
                            }
                        }
                        deadend = true;
                    }
                    break;
                //Going right
                case 4: 
                    //Blank must be to the left of the last column (size - 1) 
                    if (v.at(0) >= 0 && v.at(0) < temp-> gettunnel() -> getsize() - 1) {
                        //Look at value to the right
                        val = temp-> gettunnel() -> getnum(v.at(0) + 1, v.at(1));
                        //If we find another blank go right a level
                        if (val == 0) {
                            v.at(0)++;
                        }
                        //It is a soldier or barrier
                        else {
                            //If it is a soldier, create a new node that swaps with this soldier and add it to succs vector
                            if (val > 0 && val <= temp-> gettunnel() -> getsoldiers()) {
                                succs.push_back(graph-> addnode2(blank, temp, graph, v.at(0) + 1, v.at(1), dir));
                            }
                            //We are done with going in this direction
                            explore.pop();
                            //If we can backtrack to a blank that wasn't our blank, add new avenues to explore
                            //We also want to stop if we exceed 3 changes since we won't change direction more than 3 times
                            if (x != v.at(0) && v.at(3) < 3) {
                                for (int i = 0; i < leftright.size(); i++) {
                                    explore.push({v.at(0), y, leftright.at(i), v.at(3) + 1});
                                }
                            }
                            deadend = true;
                        }
                    }
                    //We are going out of bounds
                    else {
                        //We are done with going in this direction
                        explore.pop();
                        //If we are still our blank, add new avenues to explore
                        //We also want to stop if we exceed 3 changes since we won't change direction more than 3 times
                        if (x != v.at(0) && v.at(3) < 3) {
                            for (int i = 0; i < leftright.size(); i++) {
                                explore.push({v.at(0), y, leftright.at(i), v.at(3) + 1});
                            }
                        }
                        deadend = true;
                    }
                    break;

                default:
                    explore.pop();
                    deadend = true;
                    break;
            }
        }

    }

    return succs;
}

bool Solver::algorithm2(Graph* graph, Visitedstates* visited, int heuristic) {
    auto begin = chrono::high_resolution_clock::now();
    bool hassolution = false;
    //Get the initial state node of the graph
    graph-> getinitial() -> nodecostsetup(heuristic);
    Node* initial = graph-> getinitial();
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
        if (temp-> gettotalcost() > 28) {
            break;
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
            cout << endl;
            cout << "The best state to expand with g(n) = " << temp-> getgcost() << " and h(n) = " << temp-> gethcost() << " is" << endl;
             
            temp-> gettunnel()-> displaytunnel();
            
            
            
            cout << endl;
            cout << endl;
            //Pop that node off 
            pq.pop();
            cout << "Expanding this node..." << endl;
            //Add the successor node as one of the nodes we expanded to
            nodes++;
            
            vector<int> blanks = temp -> gettunnel() -> getblanksvec();

            //Vector for successor nodes
            vector<Node*> succs;
            //First iterate through each blank
            for (int j = 0; j < blanks.size(); j++) {

                //Then iterate through each direction for each blank
                for (int i = 0; i < 4; i++) {
                    //Collect all viable successors for the given direction and blank
                    succs = digger(j, temp, graph, i + 1);
                    
                    //Iterate through successors 
                    for (int k = 0; k < succs.size(); k++) {
                        //Access successor node from vector. If no such move exists or if the successor is the same state as the node's previous node, the successor node will be rendered as null
                        succ = succs.at(k);
                        //Make sure succ state exists
                        if (succ != nullptr) {
                            //Set up costs for succ using gcost based on designated heuristic
                            succ-> nodecostsetup(heuristic); 
                            //Check if successor has been added to the visited map  
                            if (!(visited-> checkstate(succ-> gettunnel()-> gettunnelvect()))) {
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
        }
        //Update maxpqsize if it exceeds the previous value
        if (pq.size() > maxpqsize) {
            maxpqsize = pq.size();
        } 
    }
    //Record end of algorithm and find time elapsed
    auto end = chrono::high_resolution_clock::now();
    auto elapsed = chrono::duration_cast<chrono::milliseconds>(end -  begin);
    
    string algo = "";
    switch (heuristic) {
        //1 indicates uniform cost as the only cost
        case 1:
            algo = "Uniform Cost";
            break;
        //2 indicates A* cost with misplaced tile (soldier) heuristic
        case 2: 
            algo = "A* Misplaced Tile";
            break;
        //3 indicates A* cost with manhattan heuristic between leader and starting spot
        case 3: 
        algo = "A* Manhattan Distance for Leader";
            break;

        //4 indicates A* cost with manhattan heuristic for all soldiers
        case 4: 
            algo = "A* Manhattan Distance";
            break;
        //5 indicates A* cost with euclidean heuristic
        default:
            algo = "A* Euclidean Distance";
            break;
    } 
    cout << "Time taken for " << algo << " algorithm: " << elapsed.count() << " milliseconds" << endl;
    //If there was a solution, print these results
    ofstream f;
    f.open("info.txt", ios::app);
    f << graph-> getinitial()-> gettunnel()-> getsoldiers() << " men in a trench" << endl;
    f << "Solution Results for " << algo << " algorithm: " << endl;
    printsolutionresults(nodes, maxpqsize, goaldepth);
    f.close();
    ofstream file;
    file.open("Timesheet.txt", ios::app);
    file << graph-> getinitial()-> gettunnel()-> getsoldiers() << " men in a trench" << endl;
    file << "Time taken for " << algo << " algorithm: " << elapsed.count() << " milliseconds" << endl;
    file.close();/**/
    return hassolution;
}

//Prints out the solution for the problem if it exists
void Solver::printsolution(Node* goalnode) {
    Node* temp = nullptr;
    temp = goalnode;
    stack<Node*> steps;
    //Going backwards from goal node, we add each previous node to stack. This puts each step in order
    while (temp != nullptr) {
        steps.push(temp);
        temp = temp-> getprev();
    }
    //Print out the solution starting from the original puzzle form and listing each step
    cout << "Solution: " << endl;
    cout << "\nOriginal problem: " << endl;
    cout << endl;
    //Acquire original solution and display it
    temp = steps.top();
    temp-> gettunnel()-> displaytunnel();
    steps.pop();
    int step = 0;
    //Iterate through solution steps and display them
    while (!steps.empty()) {
        step++;
        cout << step << "." << endl;
        temp = steps.top();
        temp-> gettunnel()-> displaytunnel();
        steps.pop();
        cout << endl;
    }
}