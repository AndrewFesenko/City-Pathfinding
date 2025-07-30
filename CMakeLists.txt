cmake_minimum_required(VERSION 3.29)
project(City_Pathfinding)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(City_Pathfinding
        algorithms/astar.h
        algorithms/dijkstra.h
        algorithms/graph.h
        src/main.cpp)
