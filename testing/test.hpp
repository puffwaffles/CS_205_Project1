#ifndef TEST_HPP
#define TEST_HPP
#include <iostream>
#include <cmath>
#include "../header/menu.hpp"
#include "../header/graph.hpp"
#include "../header/visitedstates.hpp"
#include "../header/node.hpp"
#include "../header/tunnel.hpp"
#include <vector>

using namespace std;

class Test {
    private:
        //Menu menu;
    public:
        Test();
        vector<int> Tunnelmaker1();
        vector<int> Tunnelmaker2();
        void Test1tunnel();
        void Test2tunnel();      
};

#endif