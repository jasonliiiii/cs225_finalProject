## Leading Question 
Given a dataset and a code base that implements some graph algorithms, we can learn the airport, airline, and route information. We are hoping to produce a general search tool to find the shortest path between departure and destination airports. When entering two locations, we will use the weighted graph to measure and compare the distance of different airplane routes between them. And eventually, we will find the shortest path between the two locations. The nodes will be the locations, the edges will be the routes, and the weight will be the distance.
## Dataset Acquisition
We plan to use datasets from openflights.org/data.html, specifically airports.dat and routes.dat. The airports dataset contains information about airports located all over the world while the routes dataset contains information about the routes among airports. 

## Data Format
As mentioned before, we will use airports.dat and routes.dat in this project. The routes.dat dataset contains 67663 routes between 3321 airports on 548 airlines, each line includes data of airline, airline id, source airports, source airports id, destination airports, destination airports id, codeshare, stops, and equipment. The airports.dat dataset contains over 10,000 airports, each line including name, airports id, etc. More information about how to retrieve that information will be illustrated in the next section. 

## Data Correction
We will use fstream and functions such as open() and close() to access the dataset and getline() to parse our data row by row. Since both of our datasets are comma-separated, we will differentiate different attributes by commas. In the process, we will ignore invalid data points (‘\N’). Once missing entries are detected in our desired column, we will then drop the whole row since the data is incomplete. We will also drop columns that are not related to our project as mentioned in the Data Format section. To be more specific, for the airport dataset, we will drop the following column: ‘IATA’, ‘ICAO’, ‘Timezone’, ‘Type’, ‘Source’, ‘DST’, and ‘Tz database time zone’. For the route dataset, we will drop the following columns: ‘Airline’, ‘Airline ID’, ‘Codeshare’, and ‘Equipment’. 

## Data Storage
We plan to create an Airport Class that contains the above-mentioned attributes to store the data entries in each row. Next, we will build a graph to incorporate the Airports class and the routes we retrieved from route.dat together. The vertices of the graph will be the different airports and the edges will be the routes between cities. In the end, after performing the algorithms we discussed in the next section, we will use a map to store the shortest path, in terms of Airports, between two cities and the two cities on the two sides of the path. The key of the map can be a pair that includes the starting place and the destination and the value of the map will be the shortest path. Since we plan to loop through the dataset, the storage cost is estimated to be O(n). 

## Algorithm 
Read file function for airport.dat, same as the constructor for airport object, has one input argument: each line in data (we will use a helper function to get each line), and it has the output: a list of object Airports with variables: id, name, city, country, latitude, longitude. We will use the strategy we discussed above in the Data Correction section to retrieve the data. Function efficiency for this algorithm is estimated to be O(n).

Read file function for routes.dat has input: each line in the dataset. The output for this function is a map, the key for the map is the Airport object, and the value of the map is a set of airports that are related to the key. Function efficiency for this algorithm is O(n).

We will also write an algorithm to convert the data we parsed into a graph. The input of the function will be the map we derived from the read file algorithm above. We will then construct a graph whose nodes are the airports. We will let the edge represent the relationship (connecting flights) between airports while the weights of the edges will be the distance. We would use the airports.dat to calculate the distance and we will use routes.dat to find the edges connecting the nodes. The output of the function will be the Graph object we have constructed. The time efficiency for this algorithm is estimated to be O(n) since we need to iterate through the map. 

Next, we will write a function to calculate the distance between two Airports based on the longitude and latitude. We have found related geographical tutorials online. The input of the algorithm will be two Airport objects, one being the starting location and the another one beting the ending location. The output will be the distance between two airports. We will use this later in our Dijkstra’s algorithm. The runtime for this is O(1). 

BFS: We will also implement the BFS algorithm to traverse through the airport graph. The input will be the airport graph we constructed and the starting airport. Depending on whether we want to traverse the whole graph or only part of the graph, we will also include an ending airport. The output for this algorithm will be a vector of graph nodes or airports that represents the shortest path (least number of flights) between two airports. The runtime for BFS is O(n).

Since the edges of our graph are weighted, we will use Dijkstra's algorithm to find the shortest path (least distance) between two airports/cities. The function will have three input arguments: departure airport, destination airport, and the graph we derived above. The output for this algorithm will be a list of the vertices (airports) of shortest path. Function efficiency for this algorithm is approximately O(logV), where V represents the number of vertices.

Kosaraju-Sharir's algorithm: We will also implement Kosaraju-Sharir’s algorithm as our uncovered graph algorithm. The purpose of utilizing this algorithm is to find the strongest connected components, and we represent them as a list of nodes for our input node (city). We will use these strongly connected components as our recommended travel cities for our users. The input for this algorithm in our project is the graph we obtained above, a node to start. The output is a list of nodes that are strongly connected to the node in our input. The Function efficiency is O(V+E), where V is vertex and E is edges. 


## Timeline
###### Week 1 (Oct 30th - Nov 5th )
Write ream contract, project proposal
Set up GitHub repository
###### Week 2 (Nov 6th - Nov 12th)
Download data set
Finish reading dataset
Write test cases on the shortest paths
###### Week 3 (Nov 13th - Nov 19th)
DFS traversal
Dijkstra’s Algorithm start
Write test cases
###### Week 4 (Nov 20th - Nov 26th)
:) Holiday
###### Week 5 (Nov 27th - Dec 3rd)
Dijkstra’s Algorithm
Graph output completed and verify with tests
Mid-Project Checkin (Nov 28th - Dec 2nd)
###### Week 6 (Dec 4th - Dec 10th )
Final presentation completed
Project report
