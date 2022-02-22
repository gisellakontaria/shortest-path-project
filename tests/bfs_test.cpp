#include "../cs225/catch/catch.hpp"
#include "../map.h"

#include <string>
#include <algorithm>

/* Test Helpers */
void testAllValuesInTraversal(vector<string> traversal, const vector<string>& nodes) {
  REQUIRE(traversal.size() == nodes.size());
  for (auto node : nodes) {
    auto it = std::find(traversal.begin(), traversal.end(), node);
    REQUIRE(it != traversal.end());
    traversal.erase(it);
  }
  REQUIRE(traversal.size() == 0);
}

void testAllValuesInTraversal(int numValues) {
  vector<string> nodes;
  vector<vector<double>> adj_mat;
  for (int i = 0; i < numValues; i++) {
    nodes.push_back(std::to_string(i));
    vector<double> adj_row(numValues, 1.0);
    adj_row[i] = 0.0;
    adj_mat.push_back(adj_row);
  }
  Map map(nodes, adj_mat);

  testAllValuesInTraversal(map.BFS(), nodes);
}

// --------------------- BFS Has Correct Traversals ------------------------- */
TEST_CASE("Correct traversal for small simple graph", "[correct-traversal][bfs-test]") {
  vector<string> nodes({"A", "B", "C", "D"});
  vector<vector<double>> adj_mat({
    {0, 1, 0, 0},
    {0, 0, 0, 1},
    {1, 0, 0, 0},
    {0, 0, 1, 0}
  });
  Map map(nodes, adj_mat);
  testAllValuesInTraversal(map.BFS(), nodes);
}

TEST_CASE("Correct traversal for larger simple graph", "[correct-traversal][bfs-test]") {
/*     ---- A   B - C   D - E   F - G   H - I   J - K
      |     |   |   |   |   |   |   |   |   |   |   |
      |     L   M   N   O   P - Q   R - S   T - U   V
      |     |   |   |   |                           |
      |     W - X   Y - Z                           |
      ----------------------------------------------
*/
  vector<string> nodes({"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K",
                        "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V",
                        "W", "X", "Y", "Z"});
  vector<vector<double>> adj_mat(26, vector<double>(26, 0));
  adj_mat[0][11] = adj_mat[1][2] = adj_mat[2][13] = adj_mat[3][4] = adj_mat[4][15] = 1;
  adj_mat[5][6] = adj_mat[6][17] = adj_mat[7][8] = adj_mat[8][19] = adj_mat[9][10] = 1;
  adj_mat[10][21] = adj_mat[11][22] = adj_mat[12][1] = adj_mat[13][24] = adj_mat[14][3] = 1;
  adj_mat[21][0] = adj_mat[22][23] = adj_mat[23][12] = adj_mat[24][25] = adj_mat[25][14] = 1;
  adj_mat[15][16] = adj_mat[17][18] = adj_mat[19][20] = adj_mat[16][5] = adj_mat[18][7] = 1;
  adj_mat[20][9] = 1;
  Map map(nodes, adj_mat);
  testAllValuesInTraversal(map.BFS(), nodes);
}

TEST_CASE("Has all nodes (Small graph with multiple components)", "[correct-traversal][bfs-test]") {
  vector<string> nodes({"A", "B", "C", "D"});
  vector<vector<double>> adj_mat({
    {0, 1, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
  });
  Map map(nodes, adj_mat);
  testAllValuesInTraversal(map.BFS(), nodes);
}

TEST_CASE("Has all nodes (Larger graph with multiple components)", "[correct-traversal][bfs-test]") {
  vector<string> nodes({"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K",
                        "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V",
                        "W", "X", "Y", "Z"});
  vector<vector<double>> adj_mat(26, vector<double>(26, 0));
  adj_mat[0][11] = adj_mat[1][2] = adj_mat[4][15] = 1;
  adj_mat[5][6] = adj_mat[6][17] = adj_mat[7][8] = adj_mat[8][19] = adj_mat[9][10] = 1;
  adj_mat[10][21] = adj_mat[14][3] = 1;
  adj_mat[21][0] = adj_mat[22][23] = adj_mat[23][12] = adj_mat[24][25] = adj_mat[25][14] = 1;
  adj_mat[15][16] = adj_mat[17][18] = 1;
  Map map(nodes, adj_mat);
  testAllValuesInTraversal(map.BFS(), nodes);
}

TEST_CASE("Correct Traversal for empty graph", "[correct-traversal][bfs-test]") {
  testAllValuesInTraversal(0);
}

TEST_CASE("Correct Traversal for graph with one node", "[correct-traversal][bfs-test]") {
  testAllValuesInTraversal(1);
}

TEST_CASE("Has all nodes for a 100 node graph", "[correct-traversal][bfs-test]") {
  testAllValuesInTraversal(100);
}

TEST_CASE("Has all nodes for a 500 node graph", "[correct-traversal][bfs-test]") {
  testAllValuesInTraversal(500);
}

TEST_CASE("Has all nodes for a 1000 node graph", "[correct-traversal][bfs-test]") {
  testAllValuesInTraversal(1000);
}

TEST_CASE("Has all nodes for a 6000 node graph", "[correct-traversal][bfs-test]") {
  testAllValuesInTraversal(6000);
}
