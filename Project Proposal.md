# CS 225 Project Proposal / Goals (ojasmor2-aayushb3-classen3-grk3)

* *Leading Goal:* From the dataset, we are trying to create a general search tool for flight paths and other information for airport routes from 2014. Our tool will be able to find the shortest paths between two airports that have the most flights between them, and can also find the most central airport in our dataset.

* *Dataset Acquisition and Processing:* We will be using the OpenFlights routes dataset (https://openflights.org/data.html#route). The website has a link to the routes dataset, titled routes.dat, and the dataset is in a CSV format. This file will be downloaded and pushed into our Github repo so that each member of the team has access to the same data. We will be using the Destination Airport and Source Airport columns of the data to create our algorithms. Prior to processing the data, our code will be checking for missing entries in the dataset. If found, the code will disregard that entire row. We will store the data in a graph implemented with its edges stored in a node-adjacency matrix (represented with a 2D vector). The graph will be a directed graph, and each column of the adjacency matrix has data for all routes to a certain airport, and all rows represent data for routes from a certain airport. The matrix will contain a “0” where there are no flights between two airports and a “weight” for when there is a path between airports. The weight will be calculated by performing (1 / # of flights) between two nodes (airports).

* Graph Algorithms:
  * *Graph data algorithm 1:* Dijkstra’s Algorithm to find the path between 2 airports that has the most number of airlines flying that path. The input will be the graph, the source airport, and the target airport. The output will be a vector of nodes that forms the path.
  * *Graph data algorithm 2 (complex or uncovered):* We will use betweenness centrality mapping to find which airport is the most important. The function will take in the directed graph as an input, and the output will be the node (airport) with the highest centrality.
  * *Graph Traversal:* We will be traversing through the graph nodes using the BFS algorithm. All the adjacent airports (unvisited nodes) will be added to a queue and each node will be visited only once.

* Efficiency:
  * *Graph data algorithm 1:* Dijkstra’s Algorithm will have a target O(n^2) and will need three inputs, the graph, a source node, and a destination node.
  * *Graph data algorithm 2 (complex or uncovered):* betweenness centrality will have a target O(n^3) time complexity and will have the graph as an input.
  * *Graph Traversal:* BFS Traversal will have a target O(n).

* Timeline:
  * 11/8 - 11/15 → Write class to load data and write tests
  * 11/15 - 11/22 → Write BFS traversal for the graph and write tests
  * 11/22 - 11/29 → Write Dijkstra’s shortest path algorithm and write tests
  * 11/29 - 12/01 → Midpoint check in (Have data loading, BFS, and Dijkstra’s algorithm completed)
  * 11/29 - 12/06 → Write Betweenness Centrality algorithm and write tests
  * 12/06 - 12/13 → Complete Results writeup, add instructions for building project, create final project presentation and get project ready for final submission.
