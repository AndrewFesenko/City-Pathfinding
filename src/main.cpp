#include "../algorithms/graph.h"
#include "../algorithms/dijkstra.h"
#include "../algorithms/astar.h"
#include <iostream>
#include <chrono>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// helper to print path
void printPath(const string& name, const vector<int>& path) {
	cout << name << " Path: ";
	int formatCount = 0;
	for (int node : path){
		formatCount++;
		if (formatCount % 8 == 0 && formatCount < path.size()) {
			cout << "\n";
		}
		if(formatCount < path.size()) {
			cout << node << " -> ";
		} else {
			cout << node;
		}
	}
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

void runAlgorithms(Graph& g){
	auto startDijkstra = chrono::high_resolution_clock::now();
	auto dijkstraPath = dijkstra(g, 11386675172, 123198914);		// this says g (graph) runs 1 through 4
	auto endDijkstra = chrono::high_resolution_clock::now();
	auto durationDijkstra = chrono::duration_cast<chrono::microseconds>(endDijkstra - startDijkstra).count();

	auto startAStar = chrono::high_resolution_clock::now();
	auto astarPath = astar(g, 1, 4);
	auto endAStar = chrono::high_resolution_clock::now();
	auto durationAStar = chrono::duration_cast<chrono::microseconds>(endAStar - startAStar).count();
	cout << "------------------Dijkstra's Algorithm------------------" << endl;
	if (!dijkstraPath.empty()) {
		cout << "  Total Cost: " << getPathCost(g, dijkstraPath) << "\n";
	} else {
		cout << "  No path found.\n";
	}
	cout << "  Time Taken: " << durationDijkstra << " us\n" << endl;

	cout << "------------------A* Algorithm------------------" << endl;
	if (!astarPath.empty()) {
		cout << "  Total Cost: " << getPathCost(g, astarPath) << "\n";
	} else {
		cout << "  No path found. \n";
	}
	cout << "  Time Taken: " << durationAStar << " us\n" << endl;

	char seePath = 'n';
	cout << "Would you like to see the paths? (y/n): ";
	cin >> seePath;
	if (seePath == 'y' || seePath == 'Y') {
		printPath("Dijkstra", dijkstraPath);
		cout << "--------------------------" << endl;
		printPath("A*", astarPath);
	}	
}

int main() {
	Graph g;

	string csv_path = "../data/city_edges_with_traffic.csv";

	ifstream file(csv_path);

	if(!file.is_open()) {
		cerr << "Error: Could not find and open file " << csv_path << endl;
		return 1;
	}

	string line;
	int lineNumber = -1;

	cout << "Reading data..." << endl;

	while(getline(file,line)) {
		lineNumber++;
		if(lineNumber == 0) {
			continue;
		}
		if (lineNumber % 10000 == 0){
			cout << "Reading edge(road) " << to_string(lineNumber) << "..." << endl;
		}

		stringstream ss(line);
		string token;
		vector<string> values;
		while(getline(ss,token,',')) {
			values.push_back(token);
		}

		if(values.size() != 9) {
			cout << "There aren't 9 values in line: " << to_string(lineNumber) << endl;
			return 1;
		}
		long long from = stoll(values[0]);
		long long to = stoll(values[1]);
		double cost = stod(values[2]);
		double x1 = stod(values[3]);
		double y1 = stod(values[4]);
		double x2 = stod(values[5]);
		double y2 = stod(values[6]);
		int road_closed = stoi(values[7]);
		double traffic_constant = stod(values[8]);
		bool open = !road_closed;

		if(!g.nodeFound(from)) g.addNode(from, x1, y1);
		if(!g.nodeFound(to)) g.addNode(to,x2,y2);
		
		g.addEdge(from,to,cost,open,traffic_constant);

	}
	cout << "Total edges read: " << lineNumber << endl;
	cout << "Data successfully read! \n" << endl;

	cout << "Welcome to our city way simulation! Please select one of the following locations:" << endl;
	cout << "Please choose one of the following initial locations:" << endl;

	cout << "1. TBA" << endl;
	cout << "2. TBA" << endl;

	cout << "Please choose one of the following destinations to end:" << endl;

	cout << "1. TBA" << endl;
	cout << "2. TBA" << endl;

	runAlgorithms(g);

	return 0;
}
