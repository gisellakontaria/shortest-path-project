#include "../cs225/catch/catch.hpp"
#include "../map.h"

#include <string>
#include <map>
#include <unordered_map>

/* Map constructor test */
TEST_CASE("Passed in file doesn't exist", "[correct-data-loading][map-test]") {
  REQUIRE_THROWS_AS(Map("tests_data/does_not_exist.txt"), std::invalid_argument);
}

TEST_CASE("Test number of nodes in graph", "[correct-data-loading][map-test]") {
  Map map("tests_data/small_dataset.txt");

  // dataset has 12 airports in total
  REQUIRE(map.getNodes().size() == 12);
}

TEST_CASE("Test loading empty dataset", "[correct-data-loading][map-test]") {
  Map map("tests_data/empty_dataset.txt");

  // empty graph
  REQUIRE(map.getNodes().size() == 0);
  REQUIRE(map.getAdjMatrix().size() == 0);
}

TEST_CASE("Test mapping of routes", "[correct-data-loading][map-test]") {
  Map map("tests_data/small_dataset.txt");
  std::unordered_map<std::string, std::vector<std::string>> routesMap = map.getRoutesMap();

  vector<std::string> dme_dest({"KZN", "NBC", "TGK", "UUA"});
  vector<std::string> cek_dest({"OVB"});
  vector<std::string> aer_dest({"KZN"});
  vector<std::string> asf_dest({"KZN", "MRV"});
  vector<std::string> ego_dest({"KGD"});

  // dataset has 5 source airports
  REQUIRE(routesMap.size() == 5);

  // check if destinations are mapped accordingly
  REQUIRE(routesMap.find("DME")->second == dme_dest);
  REQUIRE(routesMap.find("CEK")->second == cek_dest);
  REQUIRE(routesMap.find("AER")->second == aer_dest);
  REQUIRE(routesMap.find("ASF")->second == asf_dest);
  REQUIRE(routesMap.find("EGO")->second == ego_dest);
}

TEST_CASE("Test flight occurence mapping", "[correct-data-loading][map-test]") {
  Map map("tests_data/small_dataset.txt");
  Unordered_map weightsMap = map.getWeightsMap();

  // dataset has 9 distinct flights
  REQUIRE(weightsMap.size() == 9);

  // check if occurences are mapped accordingly
  REQUIRE(weightsMap.find(std::pair<std::string, std::string>("CEK", "OVB"))->second == 2);
  REQUIRE(weightsMap.find(std::pair<std::string, std::string>("AER", "KZN"))->second == 1);
  REQUIRE(weightsMap.find(std::pair<std::string, std::string>("ASF", "KZN"))->second == 1);
  REQUIRE(weightsMap.find(std::pair<std::string, std::string>("ASF", "MRV"))->second == 1);
  REQUIRE(weightsMap.find(std::pair<std::string, std::string>("DME", "KZN"))->second == 1);
  REQUIRE(weightsMap.find(std::pair<std::string, std::string>("DME", "NBC"))->second == 1);
  REQUIRE(weightsMap.find(std::pair<std::string, std::string>("DME", "TGK"))->second == 1);
  REQUIRE(weightsMap.find(std::pair<std::string, std::string>("DME", "UUA"))->second == 1);
  REQUIRE(weightsMap.find(std::pair<std::string, std::string>("EGO", "KGD"))->second == 1);
}

TEST_CASE("Test constructing adjacency matrix from data", "[correct-adjacency-matrix][map-test]") {
  Map map("tests_data/small_dataset.txt");
  vector<vector<double>> adjacency_matrix = map.getAdjMatrix();

  /*
  Adjacency Matrix should look like this:

       KGD EGO AER UUA NBC DME CEK MRV KZN OVB ASF TGK
  KGD   0   0   0   0   0   0   0   0   0   0   0   0
  EGO   1   0   0   0   0   0   0   0   0   0   0   0
  AER   0   0   0   0   0   0   0   0   1   0   0   0
  UUA   0   0   0   0   0   0   0   0   0   0   0   0
  NBC   0   0   0   0   0   0   0   0   0   0   0   0
  DME   0   0   0   0   1   0   0   0   1   0   0   1
  CEK   0   0   0   0   0   0   0   0   0  0.5  0   0
  MRV   0   0   0   0   0   0   0   0   0   0   0   0
  KZN   0   0   0   0   0   0   0   0   0   0   0   0
  OVB   0   0   0   0   0   0   0   0   0   0   0   0
  ASF   0   0   0   0   0   0   0   1   1   0   0   0
  TGK   0   0   0   0   0   0   0   0   0   0   0   0
  */

  REQUIRE(adjacency_matrix[0].size() == 12);

  // check if no route between 2 airports is set to 0 in matrix
  REQUIRE(adjacency_matrix[0][0] == 0);
  REQUIRE(adjacency_matrix[1][5] == 0);

  // check if weights are calculated and inputted correctly
  REQUIRE(adjacency_matrix[6][9] == 0.5);
  REQUIRE(adjacency_matrix[10][7] == 1);
  REQUIRE(adjacency_matrix[1][0] == 1);
}
