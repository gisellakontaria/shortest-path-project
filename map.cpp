#include "map.h"
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <float.h>
#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_set>
#include <unordered_map>

using std::string;
using std::vector;
using std::find;
using std::invalid_argument;

using namespace std;

/**
* Constructs a Map from the passed in 1D string vector of nodes and the 2D double vector that
* represents the edges in the graph.
*/
Map::Map(const vector<string>& n, const vector<vector<double> >& adj_mat)
 : adjacency_matrix(adj_mat), nodes(n) {}

Map::Map(const std::string& routesFile) {
  std::fstream file;
  file.open(routesFile, std::ios::in);
  // Throws an error if the passed in file doesn't exist
  if (!file.is_open()) throw invalid_argument("Invalid data file");

  std::string line;
  std::unordered_set<std::string> set;

  // Parses every line in the file
  while(getline(file, line)) {
    // parse source and dest airports
    size_t index = line.find(",");
    std::string curr_line = line.substr(index + 1);
    index = curr_line.find(",");
    curr_line = curr_line.substr(index + 1);
    index = curr_line.find(",");
    std::string source = curr_line.substr(0, index);
    if (source.size() == 0) continue; // Leaves current line of data if the data has missing values
    index = curr_line.find(",");
    curr_line = curr_line.substr(index + 1);
    index = curr_line.find(",");
    curr_line = curr_line.substr(index + 1);
    index = curr_line.find(",");
    std::string dest = curr_line.substr(0, index);
    if (dest.size() == 0) continue; // Leaves current line of data if the data has missing values

    // add airports to set to prevent duplicates
    set.insert(source);
    set.insert(dest);

    // map source airport to destination
    if (routesMap.find(source) == routesMap.end()) {
      // add route if not found in map
      vector<std::string> destinations;
      destinations.push_back(dest);
      routesMap.insert({source, destinations});

      // set occurence of this route to 1
      weightsMap.insert({std::pair<std::string, std::string>(source, dest), 1});
    } else {
      // update destinations vector if source airport is found in map
      auto& temp = routesMap.find(source)->second;
      if (std::find(temp.begin(), temp.end(), dest) == temp.end()) {
        temp.push_back(dest);

        // new destination so set occurrence of this route to 1
        weightsMap.insert({std::pair<std::string, std::string>(source, dest), 1});
      } else {
        // increment occurrence since route is existing in map
        std::pair<std::string, std::string> r(source, dest);
        for (auto& it : weightsMap) {
          if (it.first == r) {
            it.second += 1;
            break;
          }
        }
      }
    }
  }
  // push airports to node vector
  for (auto& node : set) {
      nodes.push_back(node);
  }

  // Closes the file
  file.close();

  int size = nodes.size();

  // resizes matrix and fill spaces with 0
  adjacency_matrix.resize(size,vector<double>(size, 0));
  populateMatrix();
}

void Map::populateMatrix() {
  // iterate through routesMap
  for (const auto& route : routesMap) {
    // get the index of source airport in the nodes vector
    std::string source = route.first;
    int row = getIndex(nodes, source);

    for (const auto& dest : route.second) {
      // get the index of destination airport in the nodes vector
      int col = getIndex(nodes, dest);

      // calculate the weight of the route
      double weight = calculateWeight(source, dest);

      // set the adjacency matrix at route to the weight
      adjacency_matrix[row][col] = weight;
    }
  }
}

int Map::getIndex(const vector<std::string>& nodes, const std::string& airport) {
  auto it = std::find(nodes.begin(), nodes.end(), airport);
  if (it != nodes.end()) {
    int index = it - nodes.begin();
    return index;
  }
  return -1;
}

double Map::calculateWeight(const std::string& source, const std::string& dest) {
  // iterate through the map that has routes as key and occurences as values
  for (const auto& route : weightsMap) {
    // if the route matches the arguments, calculate the weight (1 / # of occurences)
    if (route.first == std::pair<std::string, std::string>(source, dest)) {
      return 1 / double(route.second);
    }
  }
  return -1;
}

vector<std::string> Map::getNodes() const {
  return nodes;
}

vector<vector<double>> Map::getAdjMatrix() const {
  return adjacency_matrix;
}

std::unordered_map<std::string, std::vector<std::string>> Map::getRoutesMap() const {
  return routesMap;
}

Unordered_map Map::getWeightsMap() const {
  return weightsMap;
}

vector<string> Map::BFS() {
    vector<bool> visited(nodes.size(), false);
    vector<string> final;
    for (size_t i = 0; i < nodes.size(); i++) {
      // Runs BFS on the current node if it hasn't already been visited
      if (!visited[i]) {
        vector<string> bfsVector = BFS(i, visited);
        // Inserts result of current component into final node vector
        final.insert(final.end(), bfsVector.begin(), bfsVector.end());
      }
    }
    return final;
}

vector<string> Map::BFS(size_t begin, vector<bool>& visited) {
    queue<size_t> processQueue;
    processQueue.push(begin);
    size_t curr = begin;

    // Creates the final BFS vector
    vector<string> BFS_final;

    // Runs till there are no more nodes left to traverse
    while (!processQueue.empty()) {
        curr = processQueue.front();
        processQueue.pop();

        if (visited[curr]) continue;
        visited[curr] = true;

        // Adds the current node to the traversal
        BFS_final.push_back(nodes[curr]);

        // Finds all nodes connected to this node and adds them to the queue
        for (size_t j = 0; j < nodes.size(); j++) {
            if (curr != j && adjacency_matrix[curr][j] != 0.0) {
                processQueue.push(j);
            }
        }
    }

    return BFS_final;
}

vector<string> Map::shortestPath(string source, string destination) {
    auto src_it = find(nodes.begin(), nodes.end(), source);
    auto dest_it = find(nodes.begin(), nodes.end(), destination);
    if (src_it == nodes.end() || dest_it == nodes.end()) {
        throw invalid_argument("One or both inputs do not exist within the map");
    }
    int src_index = src_it - nodes.begin();
    int dest_index = dest_it - nodes.begin();

    // Put all nodes in visited
    vector<bool> visited;
    visited.resize(nodes.size(), false);

    // Set all nodes to be infinite (maximum double) distance, except the start which is distance 0
    vector<double> distances;
    distances.resize(nodes.size(), DBL_MAX);
    distances[src_index] = 0;

    int curr_idx = src_index;

    // Create vector storing previous indices in the shortest path tree
    vector<int> back_indices;
    back_indices.resize(nodes.size(), -1);

    // Loop through until desired node is visited or all nodes in the connected component (or the graph) are visited
    for (size_t i = 0; i < nodes.size(); ++i) {
        // Get distance of each neighbor and update current distance and back index if it is new minimum
        for (size_t j = 0; j < nodes.size(); ++j) {
            if (adjacency_matrix[curr_idx][j] > 0) {
                // Distance is distance of previous + edge weight
                double potential_dist = adjacency_matrix[curr_idx][j] + distances[curr_idx];
                if (potential_dist < distances[j]) {
                    distances[j] = potential_dist;
                    back_indices[j] = curr_idx;
                }
            }
        }

        visited[curr_idx] = true;
        // End if the current node is the destination
        if (curr_idx == dest_index) {
            break;
        }

        double min_dist = DBL_MAX;
        int min_index = -1;
        // Next curr_idx is the unvisited node with the lowest tentative distance (can't be DBL_MAX)
        for (size_t j = 0; j < nodes.size(); ++j) {
            if (visited[j] == false && distances[j] < min_dist) {
                min_dist = distances[j];
                min_index = j;
            }
        }

        if (min_index == -1) {
            // The nodes are not in the same component, return empty vector
            return vector<string>();
        }

        curr_idx = min_index;
    }

    vector<string> path;
    int path_current = dest_index;
    while (back_indices[path_current] != -1) {
        //std::cout << "Back index of " << path_current << " is "  << back_indices[path_current] << std::endl;
        path.push_back(nodes[path_current]);
        path_current = back_indices[path_current];
    }
    path.push_back(nodes[path_current]);

    std::reverse(path.begin(), path.end());
    return path;
}



string Map::calculateCentralNode() {
    if (nodes.size() == 0) {
        return "";
    }

    vector<int> frequencies;
    frequencies.resize(nodes.size(), 0);

    for (size_t idx = 0; idx < nodes.size(); ++idx) {
        // Put all nodes in visited
        vector<bool> visited;
        visited.resize(nodes.size(), false);

        // Set all nodes to be infinite (maximum double) distance, except the start which is distance 0
        vector<double> distances;
        distances.resize(nodes.size(), DBL_MAX);
        distances[idx] = 0;

        int curr_idx = idx;

        // Create vector storing previous indices in the shortest path tree
        vector<int> back_indices;
        back_indices.resize(nodes.size(), -1);

        // Loop through until desired node is visited or all nodes in the connected component (or the graph) are visited
        for (size_t i = 0; i < nodes.size(); ++i) {
            // Get distance of each neighbor and update current distance and back index if it is new minimum
            for (size_t j = 0; j < nodes.size(); ++j) {
                if (adjacency_matrix[curr_idx][j] > 0) {
                    // Distance is distance of previous + edge weight
                    double potential_dist = adjacency_matrix[curr_idx][j] + distances[curr_idx];
                    if (potential_dist < distances[j]) {
                        distances[j] = potential_dist;
                        back_indices[j] = curr_idx;
                    }
                }
            }

            visited[curr_idx] = true;
            double min_dist = DBL_MAX;
            int min_index = -1;
            // Next curr_idx is the unvisited node with the lowest tentative distance (can't be DBL_MAX)
            for (size_t j = 0; j < nodes.size(); ++j) {
                if (visited[j] == false && distances[j] < min_dist) {
                    min_dist = distances[j];
                    min_index = j;
                }
            }

            if (min_index == -1) {
                // The nodes are not in the same component, break
                break;
            }

            curr_idx = min_index;
        }

        for (size_t dest = 0; dest < nodes.size(); ++dest) {
            int path_current = back_indices[dest];
            while (path_current != -1) {
                ++frequencies[path_current];
                path_current = back_indices[path_current];
            }
        }
    }

    int max_idx = 0;
    int max_value = 0;
    for (size_t i = 0; i < frequencies.size(); ++i) {
        if (frequencies[i] > max_value) {
            max_idx = i;
            max_value = frequencies[i];
        }
    }

    return nodes[max_idx];
}
