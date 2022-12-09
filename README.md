# CS225 Final Project
### - Team Members: Jiyang Xu, Jason Li, Jian Song, Alex Li

### - Introduction: 
#### Our final project uses data sets airports.dat and routes.dat from OpenFlights to construct a graph of airport vertices and routes edges. We mainly use three algorithms: Breadth First Search, Djikstra's and Kosaraju algorithms. We traverse the whole graph by using BFS. We use Djikstra's to find the shortest path between two airports. We use Kosaraju algorithm to find the strongest connected components of a given airport. 

### - Github Organization (Our main work is located in master branch):
#### 1. Codebase is located in "src" file:
##### 1) Airport: the airport class is the vertices of our graph. Each airport is constructed with a name, an ID, a city, a country, and latitude and longitude obtaining from airports.dat
##### 2) Route: the route class is the edges of our graph. Each route is constructed with a source airport id, an destination airport id, weight obtaining from routes.dat
##### 3) Airport Graph: the airport graph class is main construction and its implementation of our graph. All of our algorithms: Breadth First Search, Djikstra's and Kosaraju algorithms are implemented in this class.

#### 2. Test cases are located in "tests" file. 

#### 3. Data sets are located in "src" file: airports.dat and routes.dat

#### 4. Our written report and presentation video is located in main branch. 

### - Running Instructions:
#### 1. Building the program:
```
mkdir build
cd build
```
#### This makes a new directory in directory called build. Then run make:
```
make
```
#### 2. We create test cases as following: Check readLineAirport, Check readLineRoute, Calculate Distance, Graph Construction, BFS, Find shortest path by distance, Find strongly connected component. 
#### To run the test cases, use
```
make test
./test
```
#### 3. To end the program anytime, use 
```
Ctrl+C
```
