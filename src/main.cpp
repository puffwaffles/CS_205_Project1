#include <iostream>
#include <cmath>
#include "../header/menu.hpp"
#include "../header/solver.hpp"
#include "../header/graph.hpp"
#include "../header/visitedstates.hpp"
#include "../header/node.hpp"
#include "../header/tunnel.hpp"

using namespace std;

int main() {
    Menu menu;
    menu.promptpuzzletype();
    menu.developpuzzle();
    menu.promptalgorithm();
    menu.beginalgorithm();
    return 0;
}

