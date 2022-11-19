#include "airport_graph.h"

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Graph::Graph(){}

Graph::Graph(string & airportFile, string routeFile) {

}

vector<Airport> readFileAP(string airportFile) {
    vector<Airport> all_aps;
    fstream file;
    file.open(airportFile, ios::in);
    if (file.is_open()) {
        string line;

        while (getline(file, line)) {
            if (Airport(&line) != nullptr) {
                all_aps.push_back(Airport(&line));
            }
        }
        file.close();
    }
    return all_aps;
}

void Graph::insertVertex(int v, Airport airport);

// helper functions to create and insert one edge (route)
// example line: BA,1355,SIN,3316,LHR,507,,0,744 777
vector<string> Graph::readLineRoute(string & line) {
    string s = "";
    vector<string> routes;
    int comma = 0;
    for (size_t i = 0; i < line.size(); ++i) {
        char c = line[i];
        // next line 
        if (c == '\\') {
            return routes;
        }
        // one element ended
        if (c == ',') {
            routes.push_back(s);
            comma++;
        } else {
            s += c;
        }
    }
    // missing component, discard line
    if (comma != 8) {
        return nullptr;
    }
    return routes;
}

Route Graph::createRoute(vector<string> route);
    if (route != nullptr) {
        int source_id = stoi(route[3], nullptr);
        int dest_id = stoi(route[5], nullptr);
        // missing part: check source airport and destination aiport are included in the vertex vector or not
        double weight = calculate_distance(source_id, dest_id);
        return Route r(source_id, dest_id, weight);
    } 
    return Route();
}

vector<Route> Graph::readFileRoute(string routeFile) {
    vector<Route> all_routes;
    fstream file;
    file.open(routeFile, ios::in);
    if (file.is_open()) {
        string line;

        while (getline(file, line)) {
            vector<string> route = readLineRoute(line);
            // check if is the skipped route
            if (route != nullptr) {
                Route r = createRoute(route);
                all_routes.push_back(r);
            }
        }
        file.close();
    }
    return all_routes;
}

