CMAKE_MINIMUM_REQUIRED(VERSION 3.30)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(AIProject1)

ADD_EXECUTABLE(test
    src/tunnel.cpp
    src/node.cpp
    src/graph.cpp
    src/visitedstates.cpp
    src/solver.cpp
    testing/test.cpp
    src/menu.cpp
    testing/testmain.cpp
)

ADD_EXECUTABLE(solve
    src/tunnel.cpp
    src/node.cpp
    src/graph.cpp
    src/visitedstates.cpp
    src/solver.cpp
    src/menu.cpp
    src/main.cpp
)