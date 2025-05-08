#ifndef NODE_HPP
#define NODE_HPP
#include <iostream>
#include <cmath>
#include "tunnel.hpp"


using namespace std;

class Node {
    private:
        int size;
        int soldiers;
        int blanks;
        Tunnel tunnel;
        Node* prev;
        vector <Node*> dirs;
        double totalcost;
        double gcost;
        double hcost; 


    public:
        Node();
        Node(int size, int soldier, int blanks);
        //Set up the previous state node. Previous state node for root is null
        void setprev(Node* node);
        //Set up the state node of the blank in a given direction. If no node exists, value is null
        void setdirs(Node* node, int direct);
        //Set up the total cost of the node to another value
        void settotalcost(double add);
        //Set up the path cost (gcost)
        void setgcost(double add);
        //Set up the heuristic cost (hcost)
        void sethcost(double add);
        //Set up total cost based on type of heuristic
        void nodecostsetup(int type);
        //Return the size of the tunnel
        int getsize();
        //Return the tunnel of the node
        Tunnel* gettunnel();
        //Return the previous state node. Returns null for root node
        Node* getprev();
        //Return the state node of the blank moving in a given direction. If no node exists, value is null
        Node* getdirs(int direct);
        //Return the total cost of the state node
        double gettotalcost();
        //Return the path cost of the state node (gcost)
        double getgcost();
        //Return the heuristic cost of the state node (hcost)
        double gethcost();
        //Calculate the heuristic cost using the misplaced soldier heuristic for a soldier
        int calcsoldiermth(int val);
        //Calculate the heuristic cost using the misplaced tile heuristic
        int calculatemth();
        //Calculate the heuristic cost using the euclidean heuristic for a soldier
        double calcsoldieredh(int val);
        //Calculate the heuristic cost using the euclidean heuristic
        double calculateedh();
        //Calculate the heuristic cost using the manhattan heuristic for a soldier
        int calcsoldiermdh(int val);
        //Calculate the heuristic cost using the manhattan heuristic
        int calculatemdh();
        //Checks if the state node is the goal state
        bool checkgoal();
        int getblanks();
};

#endif 