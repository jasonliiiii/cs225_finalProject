## Output and correctness of each algorithm

### Datasets:
Output: We had constructed two classes `Airport` and `Route` to store each line of the dataset. Then, we stored each line of the dataset in vectors that were used during the graph implementation phrase. Class `Airport`

Correctness and tests:

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

