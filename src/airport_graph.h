#pragma once

#include <vector>
#include <string>
#include <map>
#include <stack>
#include <queue>

#include <string>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>

#include "airport.h"
#include "route.h"

using namespace std;

class Graph {
    public:
    Graph();
    // in order to obtain a list of airports and routes
    Graph(string & airportFile, string & routeFile);

    /************************************************
    Suggestion: Maybe we could create two vectors, one containing all the airports and one containing all the routes
    ************************************************/
    // populate the 'vertices' map
    void setVerticesMap(vector<Airport> airports);

    // populate the 'related airports' map
    void setRelationMap(vector<Route> routes);

    // read airports.dat and get a vector of airports
    vector<Airport> readFileAP(string airportFile);

    // helper function to insert edges (routes)
    vector<string> readLineRoute(string & line);

    // helper function to convert above line to Route object
    Route createRoute(vector<string> route);

    // read routes.dat and get a vector of routes
    vector<Route> readFileRoute(string routeFile);


    /************************************************
    BFS traversal
    ************************************************/
    // helper function for BFS
    vector<int> adjacent(int sourceAP);

    // helper getter
    string getAirportNameByID(int id);

    vector<string> traverseAll(int sourceAP);

    vector<string> traverseByDest(int sourceAP, int destAP);


    /************************************************
    Dijkstras: find shortest path (recommended travel paths)
    ************************************************/

    // input: source airport and destination airport
    // output: a vector to represent the shortest path
    vector<int> dijkstras(int source_airport_id, int destination_airport_id);

    vector<int> dijkstras(string source_airport_id, string destination_airport_id);

    /**
      * Helper function to get the distance from the source airport to its adjacent airport
      * 
      * @param sourceAP The source airport
      * @param adjAP The adjacent airport whose distance from the source airport we want to know 
      * @return Distance from the source airport to the adjacent airport
      */
    int getAdjDistance(int sourceAP, int adjAP);

    /************************************************
    Kosaraju: strongest connect component (recommended travel cities)
    ************************************************/

    // input: source airport
    // output: a vector to represent the strongest connect airports in the graph
    vector<int> kosaraju(int source_airport_id);

    void dfs(int v, vector<bool> visited);

    void fillOrder(int i,  vector<bool> visited, stack<int> &stack);

    Graph transpose();

    private:

    // map each id with its airport object
    map<int, Airport> vertices;

    // a map that records the adjacent airport with routes and the distance between them
    // key: main airport, value: pairs(key: related airport, value: distance)
    map<int, set<pair<int,double>>> related_airports;

    vector<Airport> airports_;
};