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

    // functions to insert vertices (airports)
    void insertVertex(int v, Airport airport);

    // helper function to insert edges (routes)
    vector<string> readLineRoute(string & line);

    // helper function to convert above line to Route object
    Route createRoute(vector<string> route);

    vector<Route> readFileRoute(string routeFile);

    private:
    // map each id with its airport object
    map<int, Airport> vertices;

    // a map that records the adjacent airport with routes and the distance between them
    // key: main airport, value: pairs(key: related airport, value: distance)
    map<int, set<pair<int,int>>> related_aiports;
};