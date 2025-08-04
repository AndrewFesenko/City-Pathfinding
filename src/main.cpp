#include "../algorithms/graph.h"
#include "../algorithms/dijkstra.h"
#include "../algorithms/astar.h"
#include <iostream>
#include <chrono>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <thread>
#include <cctype>

using namespace std;

// helper to print path
void printPath(const string& name, const vector<long long>& path) {
	cout << name << " Path: ";
	int formatCount = 0;
	for (long long node : path){
		formatCount++;
		if (formatCount % 8 == 0 && formatCount < path.size()) {
			cout << "\n";
		}
		if(formatCount < path.size()) {
			cout << node << " -> ";
		} else {
			cout << node;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(25));
	}
	cout << "\n\n";
}

// prints path cost
double getPathCost(const Graph& g, const vector<long long>& path) {
	double cost = 0;
	for (size_t i = 0; i < path.size() - 1; ++i) {
		long long from = path[i];
		long long to = path[i + 1];
		for (const auto& edge : g.adj.at(from)) {
			if (edge.to == to && edge.isOpen) {
				cost += edge.cost * edge.trafficMultiplier;
				break;
			}
		}
	}
	return cost;
}

void runAlgorithms(Graph& g, long long startID, long long endID){
	auto startDijkstra = chrono::high_resolution_clock::now();
	auto dijkstraPath = dijkstra(g, startID, endID);
	auto endDijkstra = chrono::high_resolution_clock::now();
	auto durationDijkstra = chrono::duration_cast<chrono::microseconds>(endDijkstra - startDijkstra).count();

	auto startAStar = chrono::high_resolution_clock::now();
	auto astarPath = astar(g, startID, endID);
	auto endAStar = chrono::high_resolution_clock::now();
	auto durationAStar = chrono::duration_cast<chrono::microseconds>(endAStar - startAStar).count();
	cout << "------------------Dijkstra's Algorithm------------------" << endl;
	if (!dijkstraPath.empty()) {
		cout << "  Total Cost: " << getPathCost(g, dijkstraPath) << endl;
	} else {
		cout << "  No path found." << endl;
	}
	cout << "  Time Taken: " << durationDijkstra << " us\n" << endl;

	cout << "------------------A* Algorithm------------------" << endl;
	if (!astarPath.empty()) {
		cout << "  Total Cost: " << getPathCost(g, astarPath) << endl;
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

std::unordered_map<int,long long> landmarkMap() {
	std::unordered_map<int,long long> landmarks;
	string landmarks_path = "../data/landmarks.csv";
	ifstream file(landmarks_path);
	if(!file.is_open()) {
		cerr << "Error: Could not find and open file " << landmarks_path << endl;
		return landmarks;
	}

	string line;
	int lineNumber = -1;

	while(getline(file,line)) {
		lineNumber++;
		if(lineNumber == 0) {
			continue;
		}
		

		stringstream ss(line);
		string token;
		int token_number = -1;
		while(getline(ss,token,',')) {
			token_number++;
			if (token_number == 1) landmarks[lineNumber] = stoll(token);
		}
	}

	return landmarks;
}


bool isLandmarkID_Valid(const string& input) {
	
    // Check if string is empty
    if (input.empty()) {
        return false;
    }
    
    // Check if all characters are digits
    for (char c : input) {
        if (!isdigit(c)) {
            return false;
        }
    }
    
    // Convert to integer and check range
    int num = stoi(input);
    return (num >= 1 && num <= 16);
}
// Generated with assistance from Claude Sonnet 4 AI


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

	cout << "Loading data..." << endl;

	while(getline(file,line)) {
		lineNumber++;
		if(lineNumber == 0) {
			continue;
		}
		// if (lineNumber % 10000 == 0){
		// 	cout << "Reading edge(road) " << to_string(lineNumber) << "..." << endl;
		// }

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
		
		if(open) g.addEdge(from,to,cost,open,traffic_constant);

	}
	cout << endl << "Data successfully loaded! \n" << endl;

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	cout << " _______ __________________              _______  _______ _________            _______ _________ _        ______  _________ _        _______  _ " << endl;
	cout << R"((  ____ \\__   __/\__   __/|\     /|    (  ____ )(  ___  )\__   __/|\     /|  (  ____ \\__   __/( (    /|(  __  \ \__   __/( (    /|(  ____ \( ))" << endl;
	cout << R"(| (    \/   ) (      ) (   ( \   / )    | (    )|| (   ) |   ) (   | )   ( |  | (    \/   ) (   |  \  ( || (  \  )   ) (   |  \  ( || (    \/| |)" << endl;
	cout << R"(| |         | |      | |    \ (_) /     | (____)|| (___) |   | |   | (___) |  | (__       | |   |   \ | || |   ) |   | |   |   \ | || |      | |)" << endl;
	cout << R"(| |         | |      | |     \   /      |  _____)|  ___  |   | |   |  ___  |  |  __)      | |   | (\ \) || |   | |   | |   | (\ \) || | ____ | |)" << endl;
	cout << R"(| |         | |      | |      ) (       | (      | (   ) |   | |   | (   ) |  | (         | |   | | \   || |   ) |   | |   | | \   || | \_  )(_))" << endl;
	cout << R"(| (____/\___) (___   | |      | |       | )      | )   ( |   | |   | )   ( |  | )      ___) (___| )  \  || (__/  )___) (___| )  \  || (___) | _ )" << endl;
	cout << R"((_______/\_______/   )_(      \_/       |/       |/     \|   )_(   |/     \|  |/       \_______/|/    )_)(______/ \_______/|/    )_)(_______)(_))" << endl << endl;
	// Generated with the assistance of Claude Sonnet 4 AI

	cout << "Welcome to our city path-finding simulation!" << endl << endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	

	std::unordered_map<int,long long> landmarkNodeIDs = landmarkMap();
	cout << "Please choose one of the following landmarks to path from:" << endl;
	cout << "1. LAX Airport" << "\t\t\t" << "9. Caltech" << endl;
	cout << "2. USC" << "\t\t\t\t" << "10. The Grove" << endl;
	cout << "3. Griffith Observatory" << "\t\t" << "11. Koreatown Los Angeles" << endl;
	cout << "4. Hollywood Sign" << "\t\t" << "12. Staples Center" << endl;
	cout << "5. Santa Monica Pier" << "\t\t" << "13. Union Station Los Angeles" << endl;
	cout << "6. Dodger Stadium" << "\t\t" << "14. Exposition Park" << endl;
	cout << "7. Beverly Hills City Hall" << "\t" << "15. Echo Park Lake" << endl;
	cout << "8. The Getty Center" << "\t\t" << "16. Westwood Village" << endl;

	// cout << "1. LAX Airport" << "\t\t\t" << "9. Caltech" << endl;
	// cout << "2. USC" << "\t\t\t\t" << "10. The Grove" << endl;
	// cout << "3. Griffith Observatory" << "\t\t" << "11. Koreatown Los Angeles" << endl;
	// cout << "4. Hollywood Sign" << "\t\t\t" << "12. Staples Center" << endl;
	// cout << "5. Santa Monica Pier" << "\t\t" << "13. Union Station Los Angeles" << endl;
	// cout << "6. Dodger Stadium" << "\t\t\t" << "14. Exposition Park" << endl;
	// cout << "7. Beverly Hills City Hall" << "\t\t" << "15. Echo Park Lake" << endl;
	// cout << "8. The Getty Center" << "\t\t\t" << "16. Westwood Village" << endl;

	string startLocID;
	cin >> startLocID;
	cout << endl;

	while(!isLandmarkID_Valid(startLocID)) {
		cout << "Invalid choice. Try again." << endl;
		cin >> startLocID;
		cout << endl;
	}

	cout << "Please choose one of the following landmarks to path to:" << endl;

	cout << "1. LAX Airport" << "\t\t\t" << "9. Caltech" << endl;
	cout << "2. USC" << "\t\t\t\t" << "10. The Grove" << endl;
	cout << "3. Griffith Observatory" << "\t\t" << "11. Koreatown Los Angeles" << endl;
	cout << "4. Hollywood Sign" << "\t\t" << "12. Staples Center" << endl;
	cout << "5. Santa Monica Pier" << "\t\t" << "13. Union Station Los Angeles" << endl;
	cout << "6. Dodger Stadium" << "\t\t" << "14. Exposition Park" << endl;
	cout << "7. Beverly Hills City Hall" << "\t" << "15. Echo Park Lake" << endl;
	cout << "8. The Getty Center" << "\t\t" << "16. Westwood Village" << endl;

	string endLocID;
	cin >> endLocID;
	cout << endl;

	while(!isLandmarkID_Valid(endLocID)) {
		cout << "Invalid choice. Try again." << endl;
		cin >> endLocID;
		cout << endl;
	}


	long long startNodeID = landmarkNodeIDs[stoi(startLocID)];
	long long endNodeID = landmarkNodeIDs[stoi(endLocID)];

	runAlgorithms(g, startNodeID, endNodeID);

	return 0;
}
