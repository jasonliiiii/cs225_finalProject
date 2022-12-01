#include "airport_graph.h"

#include <vector>
#include <map>
#include <string>
#include <queue>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Graph::Graph(){}

Graph::Graph(string & airportFile, string & routeFile) {
    // DO SOMETHING
    // Create the graph
    setVerticesMap(readFileAP(airportFile));
    setRelationMap(readFileRoute(routeFile));
}

vector<Airport> Graph::readFileAP(string airportFile) {
    vector<Airport> all_aps;
    fstream file;
    file.open(airportFile, ios::in);
    if (file.is_open()) {
        string line;

        while (getline(file, line)) {
            /*
            if (Airport(line) != nullptr) {
                all_aps.push_back(Airport(line));
            }
            */
            all_aps.push_back(Airport(line));
        }
        file.close();
    }
    return all_aps;
}

// helper functions to create and insert one edge (route)
// example line: BA,1355,SIN,3316,LHR,507,,0,744 777
vector<string> Graph::readLineRoute(string & line) {
    vector<string> routes;
    string s = "";
    int comma = 0;
    for (size_t i = 0; i < line.size(); ++i) {
        char c = line[i];
        // one element ended
        if (c == ',') {
            if (s == "\\N") {
                return vector<string>();
            }
            routes.push_back(s);
            s = "";
            comma++;
        } else {
            s += c;
        }
    }
    // missing component, discard line
    if (comma != 8) {
        return vector<string>();
    }
    return routes;
}

Route Graph::createRoute(vector<string> route) {
    if (route.empty() == false) {
        int source_id = stoi(route[3], nullptr);
        int dest_id = stoi(route[5], nullptr);
        // missing part: check source airport and destination aiport are included in the vertex vector or not
        Airport a;
        double weight = a.calculate_distance(vertices.at(source_id), vertices.at(dest_id));
        Route r(source_id, dest_id, weight);
        return r;
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
            if (route.empty() == false) {
                Route r = createRoute(route);
                all_routes.push_back(r);
            }
        }
        file.close();
    }
    return all_routes;
}

void Graph::setRelationMap(vector<Route> routes) {
    for (Route route : routes) {
        if (related_airports.count(route.getSourceId()) > 0) {
            // the airport already exsits in the map
            related_airports[route.getSourceId()].insert(pair<int, double>(route.getDestId(), route.getWeight()));
        } else {
            // when the map does not contain the desired airport, we add a new pair to the map
            set<pair<int, double>> to_insert;
            to_insert.insert(pair<int, double>(route.getDestId(), route.getWeight()));
            related_airports.insert(pair<int, set<pair<int,double>>>(route.getSourceId(), to_insert));
        }
    }
}

void Graph::setVerticesMap(vector<Airport> airports) {
    for (Airport airport : airports) {
        if (vertices.count(airport.getAirportID()) > 0) {
            // the airport already exsits in the map
            // in this case we do nothing
            continue;
        } else {
            vertices.insert(pair<int, Airport>(airport.getAirportID(), airport));
        }
    }
}

/************************************************
BFS Traversal
************************************************/

vector<int> Graph::adjacent(int sourceAP) {
    set s = related_airports.at(sourceAP);
    vector<int> vec;
    for (auto i : s) {
        vec.push_back(i.first);
    }
    return vec;
}

string Graph::getAirportNameByID(int id) {
    return vertices[id].getAirportName();
}

vector<string> Graph::traverseAll(int sourceAP) {
    vector<string> ret;
    queue<int> q;
    // 14110: because there is 14110 airports in airport dataset
    vector<bool> labels(14110, false);

    q.push(sourceAP);
    // labels[sourceAP] = true; // label sourceAP (starting point) as visited

    int currentAP = sourceAP; // copy of the input id
    labels[currentAP] = true;

    while (!(q.empty())) {
        currentAP = q.front();
        ret.push_back(getAirportNameByID(currentAP));

        for (auto ap : adjacent(currentAP)) {
            if (labels[ap] == false) { // vertex is unexplored
                labels[ap] = true;
                q.push(ap);
            }
        }
        q.pop();
    }
    return ret;
}

vector<string> Graph::traverseByDest(int sourceAP, int destAP) {
    vector<string> ret;
    queue<int> q;
    // 14110: because there is 14110 airports in airport dataset
    vector<bool> labels(14110, false);

    q.push(sourceAP);
    labels[sourceAP] = true; // label sourceAP (starting point) as visited

    int currentAP = sourceAP; // copy of the input id
    labels[currentAP] = true;

    while (!(q.empty())) {
        currentAP = q.front();

        if (currentAP == destAP) { // check if we reach the destination airport
            break;
            ret.push_back(getAirportNameByID(currentAP));
        }

        ret.push_back(getAirportNameByID(currentAP));

        for (auto ap : adjacent(sourceAP)) {
            if (labels[ap] == false) { // vertex is unexplored
                labels[ap] = true;
                q.push(ap);
            }
        }
        q.pop();
    }
    return ret;
}