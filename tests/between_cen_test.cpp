#include "../cs225/catch/catch.hpp"
#include "../map.h"
#include <vector>
#include <string>

using std::vector;
using std::string;

TEST_CASE("Correct output for graph with no nodes", "[correct-node][betweenness-centrality]") {
    vector<string> nodes {};
    vector<vector<double> > adj_mat;

    Map graph = Map(nodes, adj_mat);

    REQUIRE(graph.calculateCentralNode() == "");
}

TEST_CASE("Correct central node for basic graph", "[correct-node][betweenness-centrality]") {
    vector<string> nodes { "A", "B", "C" };
    vector<vector<double> > adj_mat { {0, 1, 0}, {1, 0, 1}, {0, 1, 0} };
    
    Map graph = Map(nodes, adj_mat);
    
    REQUIRE(graph.calculateCentralNode() == "B");
}

TEST_CASE("Correct central node for graph of two nodes", "[correct-node][betweenness-centrality]") {
    vector<string> nodes { "A", "B"};
    vector<vector<double> > adj_mat { {0, 1}, {1, 0} };
    
    Map graph = Map(nodes, adj_mat);
    
    REQUIRE(graph.calculateCentralNode() == "A");
}

TEST_CASE("Correct central node when no nodes are connected (first node is chosen)", "[correct-node][betweenness-centrality]") {
    vector<string> nodes { "A", "B", "C" };
    vector<vector<double> > adj_mat { {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };
    
    Map graph = Map(nodes, adj_mat);
    
    REQUIRE(graph.calculateCentralNode() == "A");
}

TEST_CASE("Central node for graph with multiple connected components", "[correct-node][betweenness-centrality]") {
    /*

        A - B - C           B will be central because it is the central node of the larger component (it is used in more shortest paths)

        D - E

    */
    vector<string> nodes { "A", "B", "C", "D", "E" };
    vector <vector<double> > adj_mat { { 0, 1, 0, 0, 0 }, { 1, 0, 1, 0, 0}, { 0, 1, 0, 0, 0}, { 0, 0, 0, 0, 1}, {0, 0, 0, 1, 0} };

    Map graph = Map(nodes, adj_mat);
    
    REQUIRE(graph.calculateCentralNode() == "B");
}

TEST_CASE("Central node tiebreaking for graphs with multiple paths", "[correct-node][betweenness-centrality]") {
    /* 
           B      E will end up being the central node because of cheaper paths leading to it and it being connected to many other nodes
         /   \
        A -C- E
         \   /
           D
    */
   vector<string> nodes { "A", "B", "C", "D", "E" };
    vector<vector<double> > adj_mat { {0, 0.8, 0.2, 0.5, 0}, {0.8, 0, 0, 0, 0.7}, {0.2, 0, 0, 0, 0.2}, {0.5, 0, 0, 0, 0.5}, {0, 0.7, 0.2, 0.5, 0} };
    
    Map graph = Map(nodes, adj_mat);
    
    REQUIRE(graph.calculateCentralNode() == "E");
}

TEST_CASE("Central node for large graph with multiple components and paths", "[correct-node][betweenness-centrality]") {
    // Central node should be H because H has a low-cost edge to E, a low cost edge from C, and the only edges to/from I, M, and N
    vector<string> nodes({"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K",
                        "L", "M", "N"});
    vector<vector<double> > adj_mat(14, vector<double>(14, 0));

    adj_mat[7][8] = adj_mat[9][10] = adj_mat[10][9] = 0.1;
    adj_mat[6][4] = adj_mat[8][12] = 0.2;
    adj_mat[3][0] = adj_mat[7][4] = 0.3;
    adj_mat[2][7] = adj_mat[5][6] = adj_mat[12][13] = 0.4;
    adj_mat[1][3] = adj_mat[7][6] = adj_mat[5][4] = 0.5;
    adj_mat[4][2] = adj_mat[13][7] = 0.6;
    adj_mat[1][2] = adj_mat[0][5] = 0.7;
    adj_mat[0][1] = 1.0;

    Map graph = Map(nodes, adj_mat);

    REQUIRE(graph.calculateCentralNode() == "H");
}