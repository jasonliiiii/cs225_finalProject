## Output and correctness of each algorithm

### Datasets:
Output: We had constructed two classes `Airport` and `Route` to store each line of the dataset. Then, we stored each line of the dataset in vectors that were used during the graph implementation phrase. If important information, such as airport id/name, were missimng, we disgarded the whole line. `Airport` stores information such as the airport name, airport id, longtitude and latitude etc. `Routes` stores the information about the departing airport and the destination airport, which will be used later to construct the edge of our graph.

Correctness and tests: The algorithm was completed and tested on self-defined test cases and the given dataset. For our local tests, we especially tested if the vector was able to recevie and store the correct information or not. The algorithm also succesfully reads the given dataset.

### Graph Implementation:
Output: In order to store the vertices, we constructed a std::map. Since the vertices are the airports, the key of the map is the id of the Airport, while the value is the Airport object. To store the edges, we constructed another map where the key is the id of the departing airport and the value is a pair composed of the id of the destination airport and the distance between those two airports. To summarize, for our graph, the vertex is the airport, the edge is the relationship between the airports, and the weight is the distance between the airports. 

Correctness and tests: The algorithm was completed and tested on self-defined test cases. For our local tests, we tested `setVerticesMap(vector<Airport> v)` and `setRelationMap(vector<Route> v)`. These two functions takes in the vectors we derived from reading the dataset and we tested if the components in our maps match the components in the data line. 

### Dijkstra: 
Output: The input of the Dijkstra function is the id of the source airport and that of the destination airport. We iterate through all adjacent airports and updated the distance and shortest paht. We also created a vector to store previous airports visited and reversed it to output the shortest path from source airport to destination in vector<int>. The output will be a path of airports id.

Correctness and tests: Our function past the test case which tests if we can find the correct shortest path from airport 507 to airport 3127. However, it failed to work with the large dataset that should allow users to search for the shortest path from their source airport to their destination, because the time complexity does not permit it. This is also the biggest challenge we faced when implementing and testing this function. We tried to use different approaches to reduce its time complexity but we did not succeed.

### BFS:
Output: We constructed two traversal functions. One traversed the whole graph and another one traversed based on source airport and the id of the destination airport. The outputs for both of them are vectors. For the first BFS, we constructed a queue and took a normal BFS approach. For the second BFS, we also constructed a queue to traverse our data. We have also constructed a vector to keep record of previous vertices as predecessors. Once the destination airport was found, we broke the loop. At the end, we use the predecessors obtained before to get the overall path.
  
Correctness and tests: The algorithm was completed and tested on self-defined test cases as well as the given dataset. For local tests, we tested for both traversing through the whole graph and obtaining the shortest path, which is based on the least number of airports traveled. The algorithm also works on the large dataset, tested in main.

### Kosaraju:
Output: The input for our Kosaraju algorithm is the id of the source airport. Overall, we did DFS two times and transpose overall graph. First, we fill order of vertices according to finishing times in increasing order and we reversed the direction of each edge in the whole graph. Then we did DFS again to get the strongest connected components.
  
Correctness and tests: The function was completed but it failed the test cases. We tried our best and worked on it but we still couldn't figure it out. We will continue working on it to fix the algorithm.


## Answer to leading questions
Our leading question is to find the shortest path between airports. We have completed the BFS Traversal and Dijkstra so we was able to find the shortest path. By working on this project, we have a better understanding on BFS traversal and Dijkstra algorithm. We also learn a lot about kosaruju algorithm. We talked about our individual thoughts after finishing the project and found that everyone enjoyed writing the pseudo code and made it to real code.
