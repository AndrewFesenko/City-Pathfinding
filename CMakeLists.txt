cmake_minimum_required(VERSION 3.29)
project(City_Pathfinding)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(City_Pathfinding
    astar.h
    dijkstra.h
    graph.h
    main.cpp)
