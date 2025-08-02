#ifndef GRAPH_H
#define GRAPH_H

#pragma once
#include <unordered_map>
#include <vector>
#include <cmath>

using namespace std;

// represents a connection (aka road) from one node to another
struct Edge {
    long long to; // destination
    double cost; // cost of traveling (time, distance, etc. etc.)
    bool isOpen = true; // if false, the edge is closed ( so this is like us simulating the road blocked)
    double trafficMultiplier = 1.0; // multipler for cost due to traffic (this is so we can track how traffic affects the cost so like 1.0 is normal, 2.0 is heavy)
};

// for nodes in city (aka intersections)
struct Node {
    long long id; // id of node
    double x = 0.0, y = 0.0; // could remove this later, this is for A* ("A* algorithm uses heuristics to guide its search") so this is for the heuristics os lat/long or whatever metrics
};

class Graph { //manages nodes and connections
public:
    unordered_map<int, Node> nodes; //maps nodes to node struct
    unordered_map<int, vector<Edge>> adj; // node id to edge

    void addNode(long long id, double x = 0.0, double y = 0.0) {
        nodes[id] = Node{id, x, y}; // this creates an intersection in graph and assigns id (ex. use case: g.addNode(42, 3.2, 5.7) interesction 42 is at (3.2, 5.7) (mainly for a*)
    } //currently for hardcode testing coordinates and tiny graphs fill need to change later to read file or csv with like while (file >> id >> x >> y){ g.addNode(id, x, y)}
    // same for edges below g.addEdge(from, to, cost, isOpen, traffic);

    void addEdge(long long from, long long to, double cost, bool open = true, double traffic = 1.0) { // adds two way edge to nodes
        adj[from].push_back({to, cost, open, traffic});
        adj[to].push_back({from, cost, open, traffic}); // undirected
    }

    bool nodeFound(long long id) {
        auto it = nodes.find(id);
        if(it == nodes.end()) return false;
        return true;
    }
};

#endif //GRAPH_H