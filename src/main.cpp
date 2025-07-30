#include "algorithms/graph.h"
#include "algorithms/dijkstra.h"
#include "algorithms/astar.h"
#include <iostream>
#include <chrono>

using namespace std;

// helper to print path
void printPath(const string& name, const vector<int>& path) {
	cout << name << " Path: ";
	for (int node : path) cout << node << " ";
	cout << "\n";
}

// prints path cost
double getPathCost(const Graph& g, const vector<int>& path) {
	double cost = 0;
	for (size_t i = 0; i < path.size() - 1; ++i) {
		int from = path[i];
		int to = path[i + 1];
		for (const auto& edge : g.adj.at(from)) {
			if (edge.to == to && edge.isOpen) {
				cost += edge.cost * edge.trafficMultiplier;
				break;
			}
		}
	}
	return cost;
}

int main() {
	Graph g;

	// All test cases share these nodes
	g.addNode(1, 0, 0);
	g.addNode(2, 1, 0);
	g.addNode(3, 2, 0);
	g.addNode(4, 2, 1);

	// Note: some test case scenarios below were generated using ChatGPT/Github Co-Pilot to simulate
	// test 1: Basic shortest path (no traffic or closures)
	// Expected: Both Dijkstra and A* take path 1 -> 2 -> 3 -> 4 (cost = 3)
	// g.addEdge(1, 2, 1);
	// g.addEdge(2, 3, 1);
	// g.addEdge(1, 3, 5); // tempting shortcut, but too expensive
	// g.addEdge(3, 4, 1);


	// test 2: Add heavy traffic on 2 -> 3
	// Expected: Dijkstra and A* should now prefer 1 -> 3 -> 4 (cost = 6)
	// because 2 -> 3 becomes too expensive (cost = 10)
	// g.addEdge(1, 2, 1);
	// g.addEdge(2, 3, 5, true, 2.0); // Heavy traffic = 5 * 2 = 10
	// g.addEdge(1, 3, 5); // Now cheaper than 2->3
	// g.addEdge(3, 4, 1);


	// test 3: Close 2 -> 3 road entirely
	// Expected: Only valid path is 1 -> 3 -> 4
	// g.addEdge(1, 2, 1);
	// g.addEdge(2, 3, 1, false); // Closed road
	// g.addEdge(1, 3, 5); // Now only open way to 3
	// g.addEdge(3, 4, 1);


	// test 4: Edge case - no path to destination
	// Expected: Both algorithms return an empty path
	// g.addEdge(1, 2, 1);
	// g.addEdge(2, 3, 1);
	// 3 to 4 is missing -> 4 is disconnected


	// test 5: Equal-cost paths
	// Expected: Both 1->2->3->4 and 1->3->4 have same total cost
	// g.addEdge(1, 2, 1);
	// g.addEdge(2, 3, 1);
	// g.addEdge(1, 3, 2); // Same as 1->2->3
	// g.addEdge(3, 4, 1);

	auto startDijkstra = chrono::high_resolution_clock::now();
	auto dijkstraPath = dijkstra(g, 1, 4);		// this says g (graph) runs 1 through 4
	auto endDijkstra = chrono::high_resolution_clock::now();
	auto durationDijkstra = chrono::duration_cast<chrono::microseconds>(endDijkstra - startDijkstra).count();

	auto startAStar = chrono::high_resolution_clock::now();
	auto astarPath = astar(g, 1, 4);
	auto endAStar = chrono::high_resolution_clock::now();
	auto durationAStar = chrono::duration_cast<chrono::microseconds>(endAStar - startAStar).count();

	printPath("Dijkstra", dijkstraPath);
	if (!dijkstraPath.empty()) {
		cout << "  Total Cost: " << getPathCost(g, dijkstraPath) << "\n";
		cout << "  Time Taken: " << durationDijkstra << " us\n";
	} else {
		cout << "  No path found.\n";
	}

	printPath("A*", astarPath);
	if (!astarPath.empty()) {
		cout << "  Total Cost: " << getPathCost(g, astarPath) << "\n";
		cout << "  Time Taken: " << durationAStar << " us\n";
	} else {
		cout << "  No path found.\n";
	}

	return 0;
}
