#include "../cs225/catch/catch.hpp"
#include "../map.h"
#include <vector>
#include <string>

using std::vector;
using std::string;

TEST_CASE("Correct path for graph with no nodes", "[correct-path][shortest-path]") {
    Map graph = Map(vector<string>(), vector<vector<double> >());

    REQUIRE_THROWS_AS(graph.shortestPath("A", "B"), std::invalid_argument);
}

TEST_CASE("Correct path for graph with 2 nodes", "[correct-path][shortest-path]") {
    vector<string> nodes { "A", "B" };
    vector<vector<double> > adj_mat { {0, 1}, {1, 0} };
    
    Map graph = Map(nodes, adj_mat);

    vector<string> expected { "A", "B" };
    REQUIRE(graph.shortestPath("A", "B") == expected);
}

TEST_CASE("Empty path for disconnected graph", "[correct-path][shortest-path]") {
    vector<string> nodes { "A", "B" };
    vector<vector<double> > adj_mat { {0, 0}, {0, 0} };
    
    Map graph = Map(nodes, adj_mat);
    
    REQUIRE(graph.shortestPath("A", "B").empty());
}

TEST_CASE("Error thrown with invalid inputs", "[correct-path][shortest-path]") {
    vector<string> nodes { "A", "B" };
    vector<vector<double> > adj_mat { {0, 0}, {0, 0} };
    
    Map graph = Map(nodes, adj_mat);
    
    REQUIRE_THROWS_AS(graph.shortestPath("A", "C"), std::invalid_argument);
}

TEST_CASE("Inputs are case-sensitive", "[correct-path][shortest-path]") {
    vector<string> nodes { "A", "B" };
    vector<vector<double> > adj_mat { {0, 0}, {0, 0} };
    
    Map graph = Map(nodes, adj_mat);
    
    REQUIRE_THROWS_AS(graph.shortestPath("A", "b"), std::invalid_argument);
}

TEST_CASE("Correct path for a simple 4-node graph", "[correct-path][shortest-path]]") {
    vector<string> nodes { "A", "B", "C", "D" };
    vector<vector<double> > adj_mat { {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}, {1, 0, 0, 0} };
    
    Map graph = Map(nodes, adj_mat);

    vector<string> expected { "A", "B" };
    REQUIRE(graph.shortestPath("A", "B") == expected);

    expected.push_back("C");
    REQUIRE(graph.shortestPath("A", "C") == expected);

    expected.push_back("D");

    REQUIRE(graph.shortestPath("A", "D") == expected);
}

TEST_CASE("Correct path for a 3-node graph with multiple paths", "[correct-path][shortest-path]") {
    vector<string> nodes { "A", "B", "C", "D" };
    vector<vector<double> > adj_mat { {0, 1, 0, 0.1}, {0, 0, 1, 0}, {0, 0, 0, 0}, {0, 0, 0.1, 0} };
    
    Map graph = Map(nodes, adj_mat);

    vector<string> expected { "A", "D", "C" };
    REQUIRE(graph.shortestPath("A", "C") == expected);
}

TEST_CASE("Tie-breaking for equal weight paths", "[correct-path][shortest-path]") {
    vector<string> nodes { "A", "B", "C", "D" };
    vector<vector<double> > adj_mat { {0, 0.1, 0, 0.1}, {0, 0, 0.1, 0}, {0, 0, 0, 0}, {0, 0, 0.1, 0} };
    
    Map graph = Map(nodes, adj_mat);

    vector<string> expected { "A", "B", "C" };
    REQUIRE(graph.shortestPath("A", "C") == expected);
}

TEST_CASE("Shortest path doesn't involve the first neighbor checked", "[correct-path][shortest-path]") {
    vector<string> nodes { "A", "B", "C", "D" };
    vector<vector<double> > adj_mat { {0, 0.1, 0, 0.1}, {0, 0, 0.4, 0}, {0, 0, 0, 0}, {0, 0, 0.1, 0} };
    
    Map graph = Map(nodes, adj_mat);

    vector<string> expected { "A", "D", "C" };
    REQUIRE(graph.shortestPath("A", "C") == expected);
}

TEST_CASE("Shortest path has more nodes than the alternative", "[correct-path][shortest-path]") {
    vector<string> nodes { "A", "B", "C", "D" };
    vector<vector<double> > adj_mat { {0, 0, 0.4, 0.1}, {0, 0, 0.1, 0}, {0, 0, 0, 0}, {0, 0.1, 0, 0} };
    
    Map graph = Map(nodes, adj_mat);

    vector<string> expected { "A", "D", "B", "C" };
    REQUIRE(graph.shortestPath("A", "C") == expected);
}

TEST_CASE("Shortest path has less nodes than the alternative", "[correct-path][shortest-path]") {
    vector<string> nodes { "A", "B", "C", "D" };
    vector<vector<double> > adj_mat { {0, 0, 0.5, 0.2}, {0, 0, 0.2, 0}, {0, 0, 0, 0}, {0, 0.2, 0, 0} };
    
    Map graph = Map(nodes, adj_mat);

    vector<string> expected { "A", "C" };
    REQUIRE(graph.shortestPath("A", "C") == expected);
}

TEST_CASE("Large graph with multiple components and paths", "[correct-path][shortest-path]") {
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

    REQUIRE(graph.shortestPath("A", "E") == vector<string> {"A", "F", "E"});
    REQUIRE(graph.shortestPath("A", "L") == vector<string>());
    REQUIRE(graph.shortestPath("H", "M") == vector<string> {"H", "I", "M"});
    REQUIRE(graph.shortestPath("M", "H") == vector<string> {"M", "N", "H"});
    REQUIRE(graph.shortestPath("E", "B") == vector<string>());
}