#pragma once

#include <vector>
#include <string>
#include <map>

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
    Graph(string & airportFile, string routeFile);

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

    // // function to insert vertices (airports)
    // void insertVertex(int v, Airport airport);

    // // function to insert all vertices (airports) by using two private maps
    // void insertAllVertex();

    // // function to insert edges (routes)
    // void insertEdge(Route t);

    // // functions to insert all edges (routes) by using two private maps
    // void insertAllEdges();

    private:

    // map each id with its airport object
    map<int, Airport> vertices;

    // a map that records the adjacent airport with routes and the distance between them
    // key: main airport, value: pairs(key: related airport, value: distance)
    map<int, set<pair<int,double>>> related_airports;
};