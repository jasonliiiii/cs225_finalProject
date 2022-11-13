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

using namespace std;

class Graph {
    public:
    Graph();
    // in order to obtain a list of airports and routes
    Graph(string & airportFile, string routeFile);

    // functions to insert vertices
    void insertVertex(int v, Airport airport);

    // functions to create and insert edges
    vector<string> createEdge(string & line);
    Route createEdge(map<int, set<int>> routes);
    void insertEdge(Route r);

    private:
    // map each id with its airport object
    map<int, Airport> vertices;
};