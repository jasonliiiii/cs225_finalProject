#include "airport_graph.h"

#include <vector>
#include <map>
#include <string>
#include <queue>
#include <stack>
#include <list>
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
    airports_ = readFileAP(airportFile);
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


/************************************************
Dijkstras: find shortest path (recommended travel paths)
************************************************/

/**
 * Helper function to get the distance from the source airport to its adjacent airport
 * 
 * @param sourceAP The source airport
 * @param adjAP The adjacent airport whose distance from the source airport we want to know 
 * @return Distance from the source airport to the adjacent airport
 */
int Graph::getAdjDistance(int sourceAP, int adjAP) {
    set s = related_airports.at(sourceAP);
    for (auto i : s) {
        if (i.first == adjAP) {
            return i.second;
        }
    }
    // should never get here
    return -1;
}

// input: source airport and destination airport
// output: a vector to represent the shortest path
vector<int> Graph::dijkstras(int source_airport_id, int destination_airport_id) {
    // initialize all nodes as unvisited
    vector<bool> visited(14110, false);
    // initialize all nodes distance to the maxium
    vector<int> distance(14110, INT_MAX);
    // previous vector stores the shortest path
    // initialize all nodes' previous node to [source airport] ?
    vector<int> previous(14110, source_airport_id);

    // set source airport's distance to 0 and its previous node to itself
    distance[source_airport_id] = 0;
    previous[source_airport_id] = source_airport_id;

    // find the shortest path
    for (int i = 0; i < 14110; i++) {
        // find the node not visited and closest to the source
        int next;
        int min_dist = INT_MAX;
        for (int j = 0; j < 14110; j++) {
            if (!visited[j] && distance[j] < min_dist) {
                min_dist = distance[j];
                next = j;
            }
        }
        
        visited[j] = true;
        // update distance and shortest path
        for (int j : adjacent(next)) {
            if (!visited[j]) {
                int new_dist = getAdjDistance(next, j) + distance[next];
                if (new_dist < distance[j]) {
                    distance[j] = new_dist;
                    previous[j] = next;
                }
            }
        }
    }

    // return the shortest path from source airport to destination
    vector<int> shortest_path;
    int current = destination_airport_id;
    while (previous[current] != source_airport_id) {
        shortest_path.push_back(current);
        current = previous[current];
    }
    reverse(shortest_path.begin(), shortest_path.end());
    return shortest_path;
}

vector<int> Graph::dijkstras(string source_airport_id, string destination_airport_id) {
    return vector<int>(14110, 0);
}


/************************************************
Kosaraju: strongest connect component (recommended travel cities)
************************************************/

// input: source airport
// output: a vector to represent the strongest connect airports in the graph
vector<int> Graph::kosaraju(int source_airport_id) {
    stack<int> stack;
    // mark all the vertices as not visited (for first DFS)
    vector<bool> visited (14110, false);
    
    // fill vertices in stack according to finishing times
    for (size_t i = 0; i < airports_.size(); i++) {
        if (visited[i] == false) {
            fillOrder(i, visited, stack);
        }
    }

    // create a reversed graph
    Graph g = transpose();

    // mark all the vertices as not visited (for second DFS)
    for (size_t i = 0; i < airports_.size(); i++) {
        visited[i] = false;
    }

    vector<int> ret;
    // process all vertices
    while (!stack.empty()) {
        int v = stack.top();
        stack.pop();
        ret.push_back(v);

        if (!visited[v]) {
            g.dfs(v, visited);
        }
    }
    return ret;
}

void Graph::dfs(int v, vector<bool> visited) {
    visited[v] = true;
    // for (auto it = related_airports[airports_[v].getAirportID()].begin(); it != related_airports[airports_[v].getAirportID()].end(); ++it) {
    //     if (!visited[(*it).first]) {
    //         dfs((*it).first, visited);
    //     }
    // }
    for (auto ap : adjacent(airports_[v].getAirportID())) {
        if (!visited[ap]) {
            dfs(ap, visited);
        }
    }
}

void Graph::fillOrder(int i,  vector<bool> visited, stack<int> &stack) {
    visited[i] = true;
    // for (auto it = related_airports[airports_[i].getAirportID()].begin(); it != related_airports[airports_[i].getAirportID()].end(); ++it) {
    //     if (!visited[(*it).first]) {
    //         fillOrder((*it).first, visited, stack);
    //     }
    // }
    for (auto ap : adjacent(airports_[i].getAirportID())) {
        if (!visited[ap]) {
            fillOrder(ap, visited, stack);
        }
    }
    stack.push(i);
}

Graph Graph::transpose() {
    Graph g = Graph();
    for (size_t i = 0; i < airports_.size(); i++) {
        for (auto j : adjacent(airports_[i].getAirportID())) {
            Airport dest = airports_[i];
            Airport from = vertices[j];
            double distance = from.calculate_distance(from, dest);
            pair<int, double> to_insert(airports_[i].getAirportID(), distance);
            g.related_airports[j].insert(to_insert);
        }
        // for (auto it = related_airports[airports_[i].getAirportID()].begin(); it != related_airports[airports_[i].getAirportID()].end(); ++it) {
        //     int apid = (*it).second;
        //     Airport dest = vertices[apid];
        //     g.related_airports[(*it).first].insert(pair<int, double>(airports_[i], calculate_distance(airports_[i], dest)));
        // }
    }
    return g;
}