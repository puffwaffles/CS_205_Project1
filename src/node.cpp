#include <iostream>
#include <cmath>
#include <vector>
#include "../header/node.hpp"
#include "../header/tunnel.hpp"

using namespace std;


Node::Node() {
    size = 10;
    soldiers = 9;
    blanks = 4;
    tunnel = Tunnel(size, soldiers, blanks);
    prev = nullptr;
    //dirs is vector of direction nodes. up = 0, down = 1, left = 2, and right = 3
    dirs = vector<Node*>(4, nullptr);
    totalcost = 0;
    gcost = 0;
    hcost = 0;
}

Node::Node(int sizes, int soldier, int blank) {
    size = sizes;
    blanks = blank;
    soldiers = soldier;
    tunnel = Tunnel(size, soldiers, blanks);
    prev = nullptr;
    //dirs is vector of direction nodes. up = 0, down = 1, left = 2, and right = 3
    dirs.resize(4);
    dirs.at(0) = nullptr;
    dirs.at(0) = nullptr;
    dirs.at(0) = nullptr;
    dirs.at(0) = nullptr;
    totalcost = 0;
    gcost = 0;
    hcost = 0;
}

//Sets the previous node
void Node::setprev(Node* node) {
    prev = node;
}

//Sets the directional nodes for each node. Not really used much since it turns out that multiple nodes can apply to the same direction (direction switching)
void Node::setdirs(Node* node, int direct) {
    dirs.at(direct) = node;
}

//Changes general cost 
void Node::setgcost(float add) {
    gcost = add;
}

//Changes heuristic cost
void Node::sethcost(float add) {
    hcost = add;
}

//Set up costs for given heuristic
void Node::nodecostsetup(int type) {
    float mt = 0;
    float md = 0;
    float ed = 0;
    switch (type) {
        //1 indicates uniform cost as the only cost
        case 1:
            hcost = 0;
            break;
        //2 indicates A* cost with misplaced tile (soldier) heuristic
        case 2: 
            mt = calculatemth();
            hcost = mt;
            break;
        //3 indicates A* cost with manhattan heuristic between leader and starting spot
        case 3: 
            md = calcsoldiermdh(1);
            hcost = md;
            break;

        //4 indicates A* cost with manhattan heuristic for all soldiers
        case 4: 
            md = calculatemdh();
            hcost = md;
            break;
        //5 indicates A* cost with euclidean heuristic
        default:
            ed = calculateedh();
            hcost = ed;
            break;
    }
    totalcost = gcost + hcost; 
}

//Returns size of puzzle in node
int Node::getsize() {
    return size;
}

//Returns tunnel for node
Tunnel* Node::gettunnel() {
    return &tunnel;
}

//Returns parent node
Node* Node::getprev() {
    return prev;
}

//Returns directional nodes but not really used
Node* Node::getdirs(int direct) {
    return dirs.at(direct);
}

//Returns total cost 
float Node::gettotalcost() {
    return totalcost;
}

//Returns heuristic cost
float Node::gethcost() {
    return hcost;
}

//Returns general cost
float Node::getgcost() {
    return gcost;
}

//Calculate misplaced tile cost for an individual soldier
int Node::calcsoldiermth(int val) {
    float mt = 0;
    int loc1 = tunnel.getnumloc(val);
    int loc2 = val + size - 1;
    //Check if both location values match. If they don't, mt = 1
    if (loc1 != loc2) {
        mt = 1;
    }
    return mt;
}

//Calculates misplaced tile cost for all soldiers
int Node::calculatemth() {
    float mt = 0;
    for (int i = 1; i < soldiers + 1; i++) {
        mt = mt + calcsoldiermth(i);
    }
    return mt;
}


//Calculate manhattan distance for an individual soldier
int Node::calcsoldiermdh(int val) {
    float md = 0;
    //Get the coordinates for the soldier value
    vector<int> currcoor =  tunnel.getnumcoor(val);
    //All soldiers should be a column soldier value - 1 at the end
    int changex = val - 1;
    //All soldiers should be at y = 1 at the end. 
    int changey = 1;
    //Calculate absolute value of change in x
    changex = abs(currcoor.at(0) - changex) * 1.0;
    //Calculate absolute value of change in y
    changey = abs(currcoor.at(1) - changey) * 1.0;
    md = changex + changey;
    return md;
}

//Calculate manhattan distance for all soldiers
int Node::calculatemdh() {
    float md = 0;
    for (int i = 1; i < soldiers + 1; i++) {
        md = md + calcsoldiermdh(i);
    }
    return md;
}

//Calculate euclidean distnace for an individual soldier
float Node::calcsoldieredh(int val) {
    float ed = 0.0;
    //Get the coordinates for the soldier value
    vector<int> currcoor =  tunnel.getnumcoor(val);
    //All soldiers should be a column soldier value - 1 at the end
    float changex = (val - 1) * 1.0;
    //All soldiers should be at y = 1 at the end. 
    float changey = 1.0;
    //Calculate absolute value of change in x
    changex = pow((currcoor.at(0) - changex), 2) * 1.0;
    //Calculate absolute value of change in y
    changey = pow((currcoor.at(1) - changey), 2) * 1.0;
    ed = sqrt(changex + changey);
    return ed;
}

//Calculate euclidean distance for all soldiers
float Node::calculateedh() {
    float ed = 0;
    for (int i = 1; i < soldiers + 1; i++) {
        ed = ed + calcsoldieredh(i);
    }
    return ed;
}

//Check if node has reached goal state by using misplaced heuristic (it should be 0 if it is the goal state)
bool Node::checkgoal() {
    bool reached = true;
    if (calculatemth() > 0) {
        reached = false;
    }
    return reached;
}

//Return the number of blanks for the node
int Node::getblanks() {
    return blanks;
}