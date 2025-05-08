#include <iostream>
#include <map>
#include <cmath>
#include "../header/visitedstates.hpp"
#include "../header/node.hpp"

Visitedstates::Visitedstates() {

}

void Visitedstates::addstate(vector<int> v, Node node) {
    visited[v] = node;
}

map<vector<int>, Node>* Visitedstates::getvisited() {
    return &visited;
}

bool Visitedstates::checkstate(vector<int> v) {
    bool visit = false;
    if (visited.count(v) > 0) {
        visit = true;
    }
    return visit;
}

Node* Visitedstates::accessstatenode(vector<int> v) {
    Node* access = nullptr;
    if (checkstate(v)) {
        access = &(visited.at(v));
    }
    return access;
}