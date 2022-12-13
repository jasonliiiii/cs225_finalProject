## Output and correctness of each algorithm

### Datasets:
Output: We had constructed two classes `Airport` and `Route` to store each line of the dataset. Then, we stored each line of the dataset in vectors that were used during the graph implementation phrase. If important information, such as airport id/name, were missimng, we disgarded the whole line. `Airport` stores information such as the airport name, airport id, longtitude and latitude etc. `Routes` stores the information about the departing airport and the destination airport, which will be used later to construct the edge of our graph.

Correctness and tests: The algorithm was completed and tested on self-defined test cases and the given dataset. For our local tests, we especially tested if the vector was able to recevie and store the correct information or not. The algorithm also succesfully reads the given dataset.

### Graph Implementation:
Output: In order to store the vertices, we constructed a std::map. Since the vertices are the airports, the key of the map is the id of the Airport, while the value is the Airport object. To store the edges, we constructed another map where the key is the id of the departing airport and the value is a pair composed of the id of the destination airport and the distance between those two airports. To summarize, for our graph, the vertex is the airport, the edge is the relationship between the airports, and the weight is the distance between the airports. 

Correctness and tests: The algorithm was completed and tested on self-defined test cases. For our local tests, we tested `setVerticesMap(vector<Airport> v)` and `setRelationMap(vector<Route> v)`. These two functions takes in the vectors we derived from reading the dataset and we tested if the components in our maps match the components in the data line. 

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

