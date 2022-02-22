#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <utility>

using std::vector;
using std::string;

/**
 * Unordered maps do not have default hash function for std::pair as keys
 * The struct pair_hash below is a hash function created to hash a pair
 */
struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1,T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ h2;  
    }
};

 /* Route is a pair of strings (source, destination) */
using Route = std::pair<std::string, std::string>;
 
 /**
  * Unordered_map is a new unordered map specified with Route as key,
  * occurences of Route as values, and hash function pair_hash 
  * declared below as its third argument
  */ 
using Unordered_map = std::unordered_map<Route, int, pair_hash>;

class Map {
  public:
    /**
     * Constructs a Map from the passed in 1D string vector of nodes and the 2D double vector that
     * represents the edges in the graph.
     *
     * @param n A vector of strings that represents the nodes in the matrix
     * @param adj_mat A 2D vector of doubles representing the matrix in an adjacency matrix format
     */
    Map(const vector<std::string>& n, const vector<vector<double>>& adj_mat);

    /**
     * Constructor that takes in routes.dat file as a string and parses the data into nodes and adjacency matrix.
     * @param routesFile The name of the file that contains information for all the routes.
     * @throws invalid_argument exception when the passed in file doesn't exist
     */
    Map(const std::string& routesFile);

    /**
     * The default BFS alogrithm. Returns the BFS of all nodes in the graph. Creates
     * two vectors "visited" and "final" that keep track of visited nodes and the
     * final return vecotr containing all the nodes from the BFS traversal.
     *
     * @returns A vector of strings that represents all airports found in the traversal
     */
    vector<string> BFS();

    /* Getters (only used for testing) */
    vector<std::string> getNodes() const;
    vector<vector<double>> getAdjMatrix() const;
    std::unordered_map<std::string, std::vector<std::string>> getRoutesMap() const;
    Unordered_map getWeightsMap() const;

    /**
     * Uses Dijkstra's algorithm to find the walk representing the "shortest path" between two nodes,
     * i.e. the path that best balances throughput (edge weights) and number of connecting flights.
     * @param source case sensitive name of the source node
     * @param destination case sensitive name of the destination node
     * @returns Vector of string node names representing the "shortest path" walk from source to destination.
     *          If there is no path between the specified nodes, returns an empty vector.
     * @throws invalid_argument if either the source or destination are not nodes in the map
     */
    vector<std::string> shortestPath(string source, string destination);

    /**
     * Method that calculates the central node in the graph using a variation of Dijkstra's algorithm.
     * @returns A string that represents the airport that is the most central in the graph
     */
    std::string calculateCentralNode();

  private:
    /**
     * A 2D vector containing data for every edge. It will always be an n by n vector where n is the number of nodes in the graph.
     * Each row represents all the edges (flights) with a specific airport as the source. Each column represents all edges (flights)
     * with a specific destination airport. The rows/columns are ordered in the same way as the nodes vector.
     * For example, adjacency_matrix[i][j] is the flight from the airport at nodes[i] to the airport at nodes[j].
     *
     * The weight of an edge is stored at each position. All weights will be either: 0 if no flight exists from the row airport to the column airport,
     * or 1/ (# of flights from source to destination) if at least one flight exists.
     */
    vector<vector<double>> adjacency_matrix;

    /**
     * A vector containing the 3-letter (IATA) or 4-letter (ICAO) code for each airport vertex in the graph.
     * The order of this vector is the same as the ordering of the rows and columns of the adjacency_matrix.
     */
    vector<std::string> nodes;

    /**
     * An unordered map with source airport as key and a vector of its destinations as values
     */
    std::unordered_map<std::string, std::vector<std::string>> routesMap;

    /**
     * An unordered map with pair of airports (source, dest) as key and number of occurrences of flight between them as values
     */
    Unordered_map weightsMap;

    /**
     * Fills adjacency matrix with weights if route is found or 0 otherwise
     */
    void populateMatrix();

    /**
     * Returns index of a certain airport in the vector of nodes
     */
    int getIndex(const vector<std::string>& nodes, const std::string& airport);

    /**
     * Calculates weight of edge between source and dest nodes (airports)
     * Weight = (1 / # of flights) between two nodes
     */
    double calculateWeight(const std::string& source, const std::string& dest);

    /**
    * Method that returns a vector of nodes that represent the BFS for a specific connected component.
    * Takes in a size_t that is the index of the beginning node and a vector of bools that represent
    * the visited nodes. This function is used in cojuction with the default BFS() function. BFS() calls
    * this function.
    */
    vector<string> BFS(size_t begin, vector<bool>& visited);
};
