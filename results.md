## Output and correctness of each algorithm

### Datasets:
Output: We had constructed two classes `Airport` and `Route` to store each line of the dataset. Then, we stored each line of the dataset in vectors that were used during the graph implementation phrase. `Airport` stores information such as the airport name, airport id, longtitude and latitude etc. `Routes` stores the information about the departing airport and the destination airport, which will be used later to construct the edge of our graph.

Correctness and tests:
The algorithm was completed and tested through both local tests amd omlim tests. 

### Graph Implementation (not sure if need to write?):
Output: 

Correctness and tests:

### Dijkstra: 
Output: We used two Dijkstra’s functions to find the shortest path given either source airport’s id (as a int) and destination airport’s id (as a int) or source airport’s name (as a string) and destination airport’s name (as a string). We iterate through all adjacent airports and updated the distance and shortest paht. We also created a vector to store previous airports visited and reversed it to output the shortest path from source airport to destination in vector<int>.

Correctness and tests: After we implemented our Dijkstra’s functions, we realized that it is not very efficient as we have a rather big dataset. To visualize this problem, we have 14110 vertices in our graph, and our function’s runtime is approximately 14110 * 14110 (the algorithm’s O(n^2)).


### BFS:
Output:
  
Correctness and tests:

### Kosaraju:
Output:
  
Correctness and tests:


## Answer to leading questions

