#include "map.h"
#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <algorithm>

using std::cout;
using std::endl;

using std::vector;
using std::string;
using std::min;

using namespace std::chrono;

int main (int argc, char *argv[]) {
  cout << "Loading data. This may take a few minutes." << endl;
  auto start = high_resolution_clock::now();

  // Creates empty map and assigns it to a map made from the passed in file (or default if nothing passed in)
  Map map((vector<string>()), (vector<vector<double>>()));
  if (argc > 1) map = Map(argv[1]);
  else map = Map("routes.dat");

  // Calculates and prints out duration
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(stop - start);
  cout << "Data successfully loaded!" << endl;
  cout << "Time taken for loading: " << duration.count() << " ms." << endl;

  cout << "---------------------------------------------------------" << endl;
  cout << "Running BFS:" << endl;
  start = high_resolution_clock::now();

  // Runs BFS on graph
  vector<string> bfsOut = map.BFS();

  // Calculates execution time
  stop = high_resolution_clock::now();
  duration = duration_cast<milliseconds>(stop - start);
  // Prints the first 200 nodes in the BFS (or the full BFS if there are < 200 nodes)
  cout << "Showing BFS result (first 200 nodes if over 200):" << std::endl;
  cout << "[ ";
  for (int i = 0; i < min(200, (int) bfsOut.size()); i++) {
    cout << bfsOut[i];
    if (i != min(200, (int) bfsOut.size()) - 1) cout << ", ";
  }
  cout << " ]" << endl;
  cout << "Number of nodes found from BFS: " << bfsOut.size() << endl;
  cout << "Time taken for BFS: " << duration.count() << " ms." << endl;

  cout << "---------------------------------------------------------" << endl;
  cout << "Running Shortest Path:" << endl;

  // Randomly chooses a source and destination node
  string source = bfsOut[rand() % bfsOut.size()]; // CHANGE SOURCE NODE HERE
  string dest = bfsOut[rand() % bfsOut.size()];   // CHANGE DESTINATION NODE HERE
  cout << "Source Node: " << source << endl;
  cout << "Destination Node: " << dest << endl;
  cout << "Generated Shortest Path: " << endl;
  start = high_resolution_clock::now();

  // Runs the shortest path algorithm
  vector<string> shortestPath = map.shortestPath(source, dest);
  stop = high_resolution_clock::now();
  duration = duration_cast<milliseconds>(stop - start);

  // Prints out the path
  cout << "[ ";
  for (size_t i = 0; i < shortestPath.size(); i++) {
    cout << shortestPath[i];
    if (i != shortestPath.size() - 1) cout << ", ";
  }
  cout << " ]" << endl;
  cout << "Number of nodes in path: " << shortestPath.size() << endl;
  cout << "Time taken for Shortest Path: " << duration.count() << " ms." << endl;

  cout << "---------------------------------------------------------" << endl;
  cout << "Running Centrality (This will take a long while):" << endl;
  start = high_resolution_clock::now();
  string centralNode = map.calculateCentralNode(); // Runs centrality
  stop = high_resolution_clock::now();
  duration = duration_cast<milliseconds>(stop - start);
  cout << "Central Node: " << map.calculateCentralNode() << endl; // Prints out central node
  cout << "Time taken for Centrality: " << duration.count() << " ms." << endl;

  return 0;
}
