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

void Node::setprev(Node* node) {
    prev = node;
}

void Node::setdirs(Node* node, int direct) {
    dirs.at(direct) = node;
}

void Node::setgcost(double add) {
    gcost = add;
}

void Node::sethcost(double add) {
    hcost = add;
}

void Node::nodecostsetup(int type) {
    double mt = 0;
    double md = 0;
    double ed = 0;
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

int Node::getsize() {
    return size;
}

Tunnel* Node::gettunnel() {
    return &tunnel;
}

Node* Node::getprev() {
    return prev;
}

Node* Node::getdirs(int direct) {
    return dirs.at(direct);
}

double Node::gettotalcost() {
    return totalcost;
}

double Node::gethcost() {
    return hcost;
}

double Node::getgcost() {
    return gcost;
}

//Calculate manhattan distnace for an individual soldier
int Node::calcsoldiermth(int val) {
    double mt = 0;
    int loc1 = tunnel.getnumloc(val);
    int loc2 = val + size - 1;
    //Check if both location values match. If they don't, mt = 1
    if (loc1 != loc2) {
        mt = 1;
    }
    return mt;
}

int Node::calculatemth() {
    double mt = 0;
    for (int i = 1; i < soldiers + 1; i++) {
        mt = mt + calcsoldiermth(i);
    }
    return mt;
}


//Calculate manhattan distnace for an individual soldier
int Node::calcsoldiermdh(int val) {
    double md = 0;
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

int Node::calculatemdh() {
    double md = 0;
    for (int i = 1; i < soldiers + 1; i++) {
        md = md + calcsoldiermdh(i);
    }
    return md;
}

//Calculate euclidean distnace for an individual soldier
double Node::calcsoldieredh(int val) {
    double ed = 0.0;
    //Get the coordinates for the soldier value
    vector<int> currcoor =  tunnel.getnumcoor(val);
    //All soldiers should be a column soldier value - 1 at the end
    double changex = (val - 1) * 1.0;
    //All soldiers should be at y = 1 at the end. 
    double changey = 1.0;
    //Calculate absolute value of change in x
    changex = pow((currcoor.at(0) - changex), 2) * 1.0;
    //Calculate absolute value of change in y
    changey = pow((currcoor.at(1) - changey), 2) * 1.0;
    ed = sqrt(changex + changey);
    return ed;
}

double Node::calculateedh() {
    double ed = 0;
    for (int i = 1; i < soldiers + 1; i++) {
        ed = ed + calcsoldieredh(i);
    }
    return ed;
}

bool Node::checkgoal() {
    bool reached = true;
    if (calculatemth() > 0) {
        reached = false;
    }
    return reached;
}

int Node::getblanks() {
    return blanks;
}