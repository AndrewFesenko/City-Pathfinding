#ifndef ASTAR_H
#define ASTAR_H

#pragma once
#include "graph.h"
#include <queue>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <limits>
#include <set>
#include <algorithm>

using namespace std;

double heuristic(const Node& a, const Node& b) {
    return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

vector<long long> astar(Graph& graph, long long start, long long end) { // a* algorithm
    unordered_map<long long, double> gScore, fScore;
    unordered_map<long long, long long> prev;
    set<long long> visited;

    for (const auto& [id, _] : graph.nodes) { //gscore and f score
        gScore[id] = numeric_limits<double>::infinity();
        fScore[id] = numeric_limits<double>::infinity();
    }
    gScore[start] = 0;
    fScore[start] = heuristic(graph.nodes[start], graph.nodes[end]);

    using PDI = pair<double, long long>;
    priority_queue<PDI, vector<PDI>, greater<>> openSet;
    openSet.push({fScore[start], start});

    while (!openSet.empty()) {
        auto [_, current] = openSet.top(); openSet.pop();
        if (current == end) break;
        if (visited.count(current)) continue;
        visited.insert(current);

        for (const auto& e : graph.adj[current]) {
            if (!e.isOpen) continue;

            // g = cost as of now, f = g + estimated distance to the end goal
            double tentative_g = gScore[current] + e.cost * e.trafficMultiplier;
            if (tentative_g < gScore[e.to]) {
                gScore[e.to] = tentative_g;
                fScore[e.to] = tentative_g + heuristic(graph.nodes[e.to], graph.nodes[end]);
                prev[e.to] = current;
                openSet.push({fScore[e.to], e.to});
            }
        }
    }

    vector<long long> path;
    if (gScore[end] == numeric_limits<double>::infinity()) return path;

    for (long long at = end; at != start; at = prev[at])
        path.push_back(at);
    path.push_back(start);
    reverse(path.begin(), path.end());
    return path;
}

#endif //ASTAR_H
