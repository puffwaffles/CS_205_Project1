#include <iostream>
#include <cmath>
#include "../header/menu.hpp"
#include "../header/graph.hpp"
#include "../header/visitedstates.hpp"
#include "../header/node.hpp"
#include "../header/tunnel.hpp"
#include "test.hpp"
#include <vector>

using namespace std;

Test::Test() {
}

vector<int> Test::Tunnelmaker1() {
    vector<int> tunnel = {-1, 0, -1, 0, 2, 1};
    return tunnel;
}

vector<int> Test::Tunnelmaker2() {
    vector<int> tunnel = {-1, -1, 3, -1, -1, 0, 2, 0, 1, 0};
    return tunnel;
}

vector<int> Test::Tunnelmaker3() {
    vector<int> tunnel = {-1, -1, 0, -1, 0, -1, -1, 0, 5, 4, 3, 2, 1, 0};
    return tunnel;
}

vector<int> Test::Tunnelmaker4() {
    vector<int> tunnel = {-1, -1, -1, 0, -1, 0, -1, 0, -1, -1, 0, 2, 3, 4, 5, 6, 7, 8, 9, 1};
    return tunnel;
}

vector<int> Test::Tunnelmaker5() {
    vector<int> tunnel = {-1, -1, -1, 0, -1, 0, -1, 8, -1, -1, 1, 2, 3, 4, 5, 6, 0, 0, 7, 9};
    return tunnel;
}

void Test::Test1tunnel() {
    int sizes = 3;
    int soldiers = 2;
    int blanks = 2;
    Tunnel tunnel = Tunnel(sizes, soldiers, blanks);
    tunnel.copytunnel(Tunnelmaker1());
    cout << "copied tunnel" << endl;
    tunnel.displaytunnel();
    cout << "testing soldier swapping" << endl;
    vector<int> blankstart = tunnel.getblanksvec();
    cout << "swapping blank " << 0 << " down at " << blankstart.at(0) << endl;
    tunnel.swapsoldier(0, 2); 
    tunnel.displaytunnel();
    cout << "swapping blank " << 0 << " right " << blankstart.at(0) << endl;
    tunnel.swapsoldier(0, 4); 
    tunnel.displaytunnel();
    cout << "swapping blank " << 1 << " right " << blankstart.at(1) << endl;
    tunnel.swapsoldier(1, 4); 
    tunnel.displaytunnel();
    cout << "swapping blank " << 1 << " up " << blankstart.at(1) << endl;
    tunnel.swapsoldier(1, 1); 
    tunnel.displaytunnel();
    /*
    cout << "swapping blank " << blankstart << " right" << endl;
    tunnel.swapsoldier(blankstart, 4); 
    tunnel.displaytunnel();
    cout << "swapping blank " << blankstart << " down" << endl;
    tunnel.swapsoldier(blankstart, 1); 
    tunnel.displaytunnel();
    */
}

void Test::Test2tunnel() {
    int sizes = 5;
    int soldiers = 3;
    int blanks = 3;
    vector<int> v = Tunnelmaker2();
    cout << "Before graph" << endl;
    Graph graph = Graph(sizes, soldiers, blanks);
    cout << "after graph" << endl;
    graph.setinitialstate(v);
    cout << "Set initial" << endl;
    Node* initial = graph.getinitial();
    initial-> gettunnel()-> displaytunnel();
    vector<int> blanksvec = initial-> gettunnel()-> getblanksvec();
    cout << "swapping blank " << 1 << " right " << blanksvec.at(1) << endl;
    initial-> gettunnel()-> swapsoldier(1, 4); 
    initial-> gettunnel()-> displaytunnel();
    cout << "swapping blank " << 1 << " right " << blanksvec.at(1) << endl;
    initial-> gettunnel()-> swapsoldier(1, 4); 
    initial-> gettunnel()-> displaytunnel();
    cout << "swapping blank " << 1 << " right " << blanksvec.at(1) << endl;
    initial-> gettunnel()-> swapsoldier(1, 4); 
    initial-> gettunnel()-> displaytunnel();
    cout << "swapping blank " << 0 << " down at " << blanksvec.at(0) << endl;
    initial-> gettunnel()-> swapsoldier(0, 2); 
    initial-> gettunnel()-> displaytunnel();
    cout << "swapping blank " << 2 << " left " << blanksvec.at(2) << endl;
    initial-> gettunnel()-> swapsoldier(2, 3); 
    initial-> gettunnel()-> displaytunnel();
    cout << "swapping blank " << 1 << " left " << blanksvec.at(1) << endl;
    initial-> gettunnel()-> swapsoldier(1, 3); 
    initial-> gettunnel()-> displaytunnel();
    cout << "swapping blank " << 0 << " up at " << blanksvec.at(0) << endl;
    initial-> gettunnel()-> swapsoldier(0, 1); 
    initial-> gettunnel()-> displaytunnel();
    cout << "swapping blank " << 1 << " right " << blanksvec.at(1) << endl;
    initial-> gettunnel()-> swapsoldier(1, 4); 
    initial-> gettunnel()-> displaytunnel();    
    cout << "swapping blank " << 2 << " right " << blanksvec.at(2) << endl;
    initial-> gettunnel()-> swapsoldier(2, 4); 
    initial-> gettunnel()-> displaytunnel();
    cout << "swapping blank " << 1 << " right " << blanksvec.at(1) << endl;
    initial-> gettunnel()-> swapsoldier(1, 4); 
    initial-> gettunnel()-> displaytunnel();    
}

void Test::Test3tunnel() {
    int sizes = 7;
    int soldiers = 5;
    int blanks = 4;
    vector<int> v = Tunnelmaker3();
    cout << "Before graph" << endl;
    Graph graph = Graph(sizes, soldiers, blanks);
    cout << "after graph" << endl;
    graph.setinitialstate(v);
    cout << "Set initial" << endl;
    Node* initial = graph.getinitial();
    initial-> gettunnel()-> displaytunnel();
    Solver solve;
    vector<Node*> succs = solve.digger(0, initial, &graph, 2);
    for (int i = 0; i < succs.size(); i++) {
        if (succs.at(i) != nullptr) {
            succs.at(i) -> gettunnel()-> displaytunnel();
        }
    }
}

void Test::Test4tunnel() {
    int sizes = 10;
    int soldiers = 9;
    int blanks = 4;
    vector<int> v = Tunnelmaker5();
    Graph graph = Graph(sizes, soldiers, blanks);
    graph.setinitialstate(v);
    cout << "Set initial" << endl;
    Node* initial = graph.getinitial();
    initial-> gettunnel()-> displaytunnel();
    Solver solve;
    vector<Node*> succs = solve.digger(2, initial, &graph, 4);
    for (int i = 0; i < succs.size(); i++) {
        if (succs.at(i) != nullptr) {
            succs.at(i) -> gettunnel()-> displaytunnel();
        }
    }
}