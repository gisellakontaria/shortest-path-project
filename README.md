# Final Project README
## Collaborators
* Aayush Bhat
* Ojas Mor
* Gisella Kontaria
* Christian Classen

## Code/Deliverables' Location
* Code for all algorithms contained in `Map` class (`map.cpp` and `map.h`)
* Code for all tests contained in `tests` folder
* Main executable code in `main.cpp`
* Data for loading tests in `tests_data` folder
* Main data in `routes.dat`
* Project Proposal (Goals) in `Project Proposal.md`
* Development log in `Development Log.md`
* Results report in `Results.md`
* Final Presentation on Youtube ([Link Here](https://youtu.be/Ssvj20KYVA0))

## Build/Running Instructions
#### Main Executable
* Clone repository
* Navigate to the repository directory
* (Only if on EWS) Run `module load llvm/6.0.1`
* Run `make final_graph` to build the main executable
* Run `./final_graph` to run the executable
  * To change the data file used to create the graph run `./final_graph <path_to_data_file>`. By default, the main executable loads the graph from routes.dat
  * To change the nodes used for the shortest path algorithm, change lines 56 and 57 in `main.cpp`
  * The main executable runs the BFS, Shortest Path, and Betweenness Centrality algorithms on the loaded graph

#### Tests
* Clone repository
* Navigate to the repository directory
* (Only if on EWS) Run `module load llvm/6.0.1`
* Run `make test` to build the test suite
* Run `./test` to run the entire test suite

## Methods input/output
* `Map` - Constructor that builds the graph from data read from the passed in file
  * Inputs:
    * `std::string routesFile` - The name of the file that contains the graph data
  * Outputs: None
* `BFS` - Method that returns BFS traversal of graph
  * Inputs: None
  * Outputs:
    * `std::vector<std::string>` - All nodes found in graph using BFS
* `shortestPath` - Method that returns the shortest path from source node to destination node
  * Inputs:
    * `std::string source` - The source node
    * `std::string destination` - The destination node
  * Outputs:
    * `vector<std::string>` - All nodes in path from source to destination
* `calculateCentralNode` - Calculates the Central node in the graph
  * Inputs: None
  * Outputs:
    * `std::string` - The most central node in the graph

## Data formatting
The data for the routes is formatted as follows:<br />
> `{Airline}, {Airline ID}, {Source airport}, {Source airport ID}, {Destination airport}, {Destination airport ID}, {Codeshare}, {Stops}, {Equipment}`

An example is as follows:
> `BA,1355,SIN,3316,LHR,507,,0,744 777`

The data we use to generate the graph are the {Source Airport} and {Destination Airport} elements as Source and Destination nodes respectively.


## Test Suite
The test suite contains tests for the BFS, Shortest Path, and Betweenness Centrality algorithms as well as tests for loading in data.
* BFS Test: Contained in `tests/bfs_test.cpp`
  * Contains tests for small and medium graphs with 0 connected components and some with multiple connected components
  * Has large scale tests for graphs with 6000 nodes and edge cases like graphs with 0 or 1 nodes
* Shortest Path Tests: Contained in `tests/dijkstra_test.cpp`
  * Has tests for graphs with no nodes, disconnected graphs, invalid inputs, tie-breaking, multiple components, and simple graphs of varying sizes
* Betweenness Centrality Tests: Contained in `tests/between_cen_test.cpp`
  * Has tests for graphs with no nodes, disconnected graphs, invalid inputs, tie-breaking, multiple components, and simple graphs of varying sizes
* Data Loading Tests: Contained in `tests/map_test.cpp`
  * Contains tests for empty files, valid weights for a small data size, correct nodes loaded for small dataset, and tests for helper methods
