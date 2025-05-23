#include <iostream>
#include <cmath>
#include "../header/menu.hpp"
#include "../header/solver.hpp"
#include "../header/graph.hpp"
#include "../header/node.hpp"
#include "../header/tunnel.hpp"

Menu::Menu() {
    puzzletype = 0;
    puzzlesize = 1;
    soldiers = 0;
    blanks = 0;
    algorithm = 0;
}

void Menu::promptpuzzletype() {
    cout << endl;
    //Prompt user for puzzle type
    cout << "Welcome to 862289397 puzzle solver" << endl;
    cout << "1. Default puzzle" << endl;
    cout << "2. Enter your own puzzle" << endl;
    cout << "Please choose the type of puzzle to solve (1-2): ";
    cin >> puzzletype;
    switch(puzzletype) {
        //Create default puzzle
        case 1:
            promptdefault();
            break;
        //Prompt user for puzzle contents
        case 2:
            promptpuzzlesize();
            promptpuzzle();
            break;
        default:
            cout << "Error: invalid input" << endl;
            break;
    }
}

void Menu::promptdefault() {
    cout << "Default puzzle options" << endl;
    cout << "1. 2 soldiers" << endl;
    cout << "2. 3 soldiers" << endl;
    cout << "3. 5 soldiers" << endl;
    cout << "4. 7 soldiers" << endl;
    cout << "5. 9 soldiers" << endl;

    cout << "Please choose one of the default puzzles to solve (1-5): ";
    int def = 0;
    cin >> def;
    switch(def) {
        //2 soldiers
        case 1:
            makedefault2();
            break;
        //3 soldiers
        case 2:
            makedefault3();
            break;
        //5 soldiers
        case 3:
            makedefault();
            break;
        //7 soldiers
        case 4:
            makedefault5();
            break;
        //9 soldiers
        case 5:
            makedefault4();
            break;
        default:
            cout << "Error: invalid input" << endl;
            break;
    }
}

vector<int> Menu::makedefault() {
    puzzlesize = 7;
    initial.resize(puzzlesize * 2);
    soldiers = 5;
    blanks = 4;
    //Hard coded 5 soldiers in a trench puzzle
    //X X   X   X X
    //  2 3 4 5 1
    vector<int> tunnel = {-1, -1, 0, -1, 0, -1, -1, 0, 5, 4, 3, 2, 1, 0};
    initial = tunnel;
    return tunnel;
}/**/

vector<int> Menu::makedefault2() {
    puzzlesize = 3;
    initial.resize(puzzlesize * 2);
    soldiers = 2;
    blanks = 2;
    //Hard coded 2 soldiers in a trench puzzle
    //X   X  
    //  2 1 
    vector<int> tunnel = {-1, 0, -1, 0, 2, 1};
    initial = tunnel;
    return tunnel;
}/**/

vector<int> Menu::makedefault3() {
    puzzlesize = 5;
    initial.resize(puzzlesize * 2);
    soldiers = 3;
    blanks = 3;
    //Hard coded 3 soldiers in a trench puzzle
    //X X   X X   
    //  2 3 1  
    vector<int> tunnel = {-1, -1, 0, -1, -1, 0, 2, 3, 1, 0};
    initial = tunnel;
    return tunnel;
}/**/

vector<int> Menu::makedefault4() {
    puzzlesize = 10;
    initial.resize(puzzlesize * 2);
    soldiers = 9;
    blanks = 4;
    //Hard coded 9 soldiers in a trench puzzle
    //X X X   X   X   X X
    //  2 3 4 5 6 7 8 9 1
    vector<int> tunnel = {-1, -1, -1, 0, -1, 0, -1, 0, -1, -1, 0, 2, 3, 4, 5, 6, 7, 8, 9, 1};
    initial = tunnel;
    return tunnel;
}

vector<int> Menu::makedefault5() {
    puzzlesize = 9;
    initial.resize(puzzlesize * 2);
    soldiers = 7;
    blanks = 4;
    //Hard coded 7 soldiers in a trench puzzle
    //X X X   X   X X X
    //  2 3 4 5 6 7 1  
    vector<int> tunnel = {-1, -1, -1, 0, -1, 0, -1, -1, -1, 0, 2, 3, 4, 5, 6, 7, 1, 0};
    initial = tunnel;
    return tunnel;
}

void Menu::promptpuzzlesize() {
    cout << endl;
    //Prompt user for puzzle length
    cout << "Please enter the puzzle length: ";
    cin >> puzzlesize;
    if (puzzlesize <= 0) {
        puzzlesize = 10;
    }
    //Acquire number of soldiers
    cout << "Please enter the number of soldiers: ";
    cin >> soldiers;
    if (soldiers <= 0 || soldiers >= puzzlesize) {
        soldiers = puzzlesize - 1;
    }
    int length = puzzlesize * 2;
    //Set initial and goal state tunnel sizes
    initial.resize(length);
    goal.resize(length);
}

void Menu::promptpuzzle() {
    cout << endl;
    //Prompt user for initial tunnel values
    int num = 0;
    int k = puzzlesize;
    cout << "Developing a puzzle of length " << puzzlesize << " with " << soldiers << " soldiers" << endl;
    cout << "Please enter the first row of your puzzle, use a zero to represent the blanks and -1s for barriers" << endl;
    cout << endl;
    //Acquire first row of barriers and holes
    cout << "First row: ";
    for (int i = 0; i < initial.size() / 2; i++) {
        cin >> num;
        if (num == 0) {
            initial.at(i) = 0;
            blanks++;
        } 
        else {
            initial.at(i) = -1;
        }

    }
    //Acquire second row with soldiers and holes
    cout << endl;
    cout << "Please enter the values of second row of your puzzle, using a 0 for blank spaces" << endl;
    cout << "You must enter the each soldier number once and soldier numbers must be from 1 to the total number of soldiers" << endl;
    cout << endl;
    cout << "Second row: ";
    for (int j = puzzlesize; j < initial.size(); j++) {
        cin >> num;
        initial.at(j) = num;
        if (num == 0) {
            blanks++;
        }
    }
}

void Menu::promptalgorithm() {
    cout << endl;
    //Prompt user for algorithm choice
    cout << "Enter your choice of algorithm" << endl;
    cout << "1. Uniform Cost Search" << endl;
    cout << "2. A* with the Misplaced Tile heurisitic" << endl;
    cout << "3. A* with the Manhattan distance based on leader heurisitic" << endl;
    cout << "4. A* with the Manhattan distance heurisitic" << endl;
    cout << "5. A* with the Euclidean distance heurisitic" << endl;
    cout << "Please choose the type of puzzle to solve (1-5): ";
    cin >> algorithm;
    cout << endl;
}

//Must be called after initial state has been determined
void Menu::developpuzzle() {
    //Set the initial state of the graph using the initial vector for the tunnel vector
    graph = Graph(puzzlesize, soldiers, blanks);
    graph.setinitialstate(initial);
    cout << endl;
    
    //Set up the goal state
    goal.resize(initial.size());
    goal = initial;
    //Set up correct order for second row
    for (int i = 0; i < goal.size(); i++) {
        //Setting holes as empty
        if (i < puzzlesize && goal.at(i) != -1) {
            goal.at(i) = 0;
        }
        //Set up soldiers in order
        else if (i >= puzzlesize && i <= puzzlesize + soldiers - 1) {
            goal.at(i) = i - puzzlesize + 1;
        }
        //Clear up remaining holes at the back
        else if (i > puzzlesize + soldiers - 1) {
            goal.at(i) = 0;
        }
    }
    cout << "Puzzle created: " << endl;
    graph.getinitial()-> gettunnel()-> displaytunnel();
    //Set the goal state of the graph
    graph.setgoalstate(goal);
}

void Menu::beginalgorithm() {
    bool solved = false;
    cout << "\nBeginning algorithm..." << endl;
    //Use algorithm to solve puzzle
    solved = solver.algorithm2(&graph, &visited, algorithm);
    //Message for when algorithm fails to find a solution
    if (solved == false) {
        cout << "Puzzle can not be solved" << endl;
    }
}

//Retrieves graph for menu
Graph* Menu::getgraph() {
    return &graph;
}
