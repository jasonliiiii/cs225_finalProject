## Leading Question 
Given a dataset and a code base that implements some graph algorithms, we can learn the airport, airline, and route information. We are hoping to produce a general search tool. When enter two locations, we will use weighted-graph to measure and compare the distance of different airplane routes between them. And eventually we will find the shortest path between the two locations. The nodes will be the locations, the edges will be the routes, and the weight will be the distance.
## Dataset Acquisition
We plan to use the OpenFlights datasets that are posted on the course website. This dataset contains information about numerous flights all over the world.

## Data Format
As mentioned before, the OpenFlights dataset is a open source data set of flight routes and airports. The input format is a .dat file. The dataset contains 14110 datapoints and we plan to use all of them since we plan to use the dataset that only contains the flight information. 

## Data Correction
We will use fstream and related functions (such as open(), close(), etc.) to parse our data. We will write a helper function that checks if each data point has reasonable entries and we will throw the whole row of data away if there are unreasonable or missing entries. 

## Data Storage
We plan to create an Airport Class that contains various privates variables to store the data entries each row. Next, we will build a vector on heap to store the Airport objects. The estimated storage costs for our dataset will likely be O(n) since it is a vector. Later, we will write a helper function to organize the datapoints into a graph for later usage.

## Algorithm 
Function input: The expected input will likely be the two Airports classes in our created graph. As mentioned before, we will have to transfer our data points stored in the vector into a graph that are weighted by distance between different airports. In order to find the shortest distance, we might also need to implement graph traversal algorithms utilizing data structures such as stack or queue. 
	
Function Outputs: The output for my algorithm is the route for the shortest path between two locations (city). Our algorithm will return a list containing the nodes (airports) in the graph that has the shortest distance. 

Function efficiency: The estimated runtime for our algorithm is O(n). 

## Timeline
### Week 1 (Oct 30th - Nov 5th )
1. Write ream contract, project proposal
2. Set up github repository
Write development log1
### Week 2 (Nov 6th - Nov 12th)
1. Download data set
2. Store data set
3. Write test cases
### Week 3 (Nov 13th - Nov 19th)
1. Mid-Project Checkin (Nov 14-18)
2. Implement finding shortest path
3. Write test cases
### Week 4 (Nov 20th - Nov 26th)
1. Finish finding shortest path 
2. Write test cases
### Week 5 (Nov 27th - Dec 3rd)
1. Finish any remaining parts
2. Write test cases 
### Week 6 (Dec 4th - Dec 10th )
1. Clean up code
2. Give presentation

