# Results

## Graph data loading
* Project statement: We created a constructor for the graph that takes in a string (the file where the data is located), and parses through the file to correctly load the graph into an adjacency matrix, applying the correct weights.
* Result: Loading a graph from the full dataset took 162154 milliseconds (2 min 42 sec). The loading constructor also passed all tests, giving us confidence that it works correctly.

## Graph data algorithms
### Dijkstra’s Algorithm:
* <b>Project statement</b>: Dijkstra’s Algorithm to find the path between 2 airports that has the most number of airlines flying that path (the best throughput). The input will be the source airport and the target airport. The output will be a vector of nodes that forms the path.
* <b>Result</b>: A run of Dijkstra’s Algorithm took 249 milliseconds when using the full dataset, and yielded the path CRM → MNL → DXB → JED → ASM when running the algorithm on CRM as the source and ASM as the destination. The algorithm also passed all tests written for it.
* <b>Planned efficiency</b>:  O(n<sup>2</sup>)
* <b>Achieved efficiency</b>: O(n<sup>2</sup>)

### Betweenness Centrality (complex or uncovered algorithm):
* <b>Project statement</b>: We will use betweenness centrality mapping to find which airport is the most ‘central’, meaning it is included in the highest number of shortest paths between nodes in the graph. The function will have no inputs, and the output will be the node (airport) with the highest centrality.
* <b>Result</b>:  The algorithm passed all tests written for it. For the full dataset, it showed that the most central airport was the LHR (Heathrow) airport, which makes sense because Heathrow is the largest airport in the UK, and London has some of the most airport traffic of any city in the world. For a single run of the dataset, it took 1162038 milliseconds (19 min 22 sec), which matches our expected efficiency, with a little bit of variance due to different allocation of hardware resources.
* <b>Planned efficiency</b>: O(n<sup>3</sup>)
* <b>Achieved efficiency</b>: O(n<sup>3</sup>)

### Graph Traversal (BFS):
* <b>Project statement</b>: We will be traversing through the graph nodes using the BFS algorithm. All the adjacent airports (unvisited nodes) will be added to a queue and each node will be visited only once. It will take in no inputs and return all nodes in the graph found during the BFS traversal.
* <b>Result</b>: The BFS algorithm works as planned, but the efficiency is worse than what we planned. This is mainly due to the fact that our graph representation was an adjacency matrix. While it is impossible to do a BFS graph traversal in O(n) time, the adjacency matrix bumped it up from O(n + m) to O(n2). The tests confirm that BFS returns a vector containing all nodes that are in the graph. A run of BFS took 123 milliseconds when using the full dataset.
* <b>Planned efficiency</b>: O(n)
* <b>Achieved efficiency</b>: O(n<sup>2</sup>)

## Final Results:
In the end, we were able to successfully create methods that could serve as a framework for a tool that would find the paths between two airports with the most flights, the central-most airport, and a BFS traversal of all airports in the dataset. We were able to get almost all the methods within our specified efficiency except BFS (but only because our specified bound was impossible), and were able to find out interesting information, like LHR being the central most airport in our dataset.
