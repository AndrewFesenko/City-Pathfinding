#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#pragma once
#include "graph.h"
#include <queue>
#include <unordered_map>
#include <vector>
#include <limits>
#include <set>
#include <algorithm>

using namespace std;

vector<int> dijkstra(Graph& graph, int start, int end) {
    if (graph.nodes.find(start) == graph.nodes.end()){
        return {};
    }
    unordered_map<int, double> dist; //shortest known distance
    unordered_map<int, int> prev; // previous node on the shortest path
    set<int> visited;

    for (const auto& [id, _] : graph.nodes)
        dist[id] = numeric_limits<double>::infinity();
    dist[start] = 0;

    using PDI = pair<double, int>; // priority queue for nodes to explore, ordered by distance
    priority_queue<PDI, vector<PDI>, greater<>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (visited.count(u)) continue;
        visited.insert(u);

        for (const auto& e : graph.adj[u]) {
            if (!e.isOpen) continue;

            double newDist = dist[u] + e.cost * e.trafficMultiplier;
            if (newDist < dist[e.to]) {
                dist[e.to] = newDist;
                prev[e.to] = u;
                pq.push({newDist, e.to});
            }
        }
    }

    vector<int> path;
    if (dist[end] == numeric_limits<double>::infinity()) return path;

    for (int at = end; at != start; at = prev[at])
        path.push_back(at);
    path.push_back(start);
    reverse(path.begin(), path.end());
    return path;
}

#endif //DIJKSTRA_H