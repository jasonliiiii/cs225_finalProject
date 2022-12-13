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
#include <limits.h>
#include <algorithm>

using namespace std;

Graph::Graph(){}

Graph::Graph(string airportFile, string routeFile) {
    // DO SOMETHING
    // Create the graph
    setVerticesMap(readFileAP(airportFile));
    setRelationMap(readFileRoute(routeFile));
    airports_ = readFileAP(airportFile);
}

Airport Graph::readLineAP(string& line) {
    string s = "";
    vector<string> information;
    Airport to_return = Airport();
    for (size_t i = 0; i < line.size(); i++) {
        char c = line[i];
        bool quotation = false;
        // no quotation mark occurs
        if (quotation == false) {
            // if current char is ",", which means we reach the end of one piece of information
            // pushback string s and reset s;
            if (c == ',') {
                information.push_back(s);
                s = "";
            // if current char is the first half of quotation mark,  
            } else if (c == '"') {
                quotation = true;
            // regular char
            } else {
                s += c;
            }
        // quotation mark occurs
        } else {
            // if current char is the second half of quotation mark
            if (c == '"' && i < line.size() - 1) {
                // if the next char is still the first half of quotation mark 
                if (line[i+1] == '"') {
                    s += '"';
                    i++;
                } else {
                    quotation = false;
                }
            } else {
                s += c;
            }
        }
    }
    if (information.at(0) == "\\N" || information.at(1) == "\\N" || information.at(2) == "\\N" 
    || information.at(3) == "\\N" || information.at(6) == "\\N" || information.at(7) == "\\N" || information.size() > 13) {
        return Airport(-1, "", "", "", -1, -1);
    }
    to_return.setAirportID(stoi(information[0], nullptr));
    to_return.setAirportName(information[1]);
    to_return.setAirportCity(information[2]);
    to_return.setAirportCountry(information[3]);
    to_return.setAirportLatitude(stod(information[6], nullptr));
    to_return.setAirportLongitude(stod(information[7], nullptr));
    return to_return;
}

vector<Airport> Graph::readFileAP(string airportFile) {
    vector<Airport> all_aps;
    fstream file;
    file.open(airportFile, ios::in);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            Airport a = readLineAP(line);
            if (a.getAirportID() == -1) continue;
            all_aps.push_back(a);
        }
        file.close();
    } else {
        cout << "The file fails to open" << endl;
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
        if (vertices.find(source_id) != vertices.end() && vertices.find(dest_id) != vertices.end()) {
            Airport a;
            double weight = a.calculate_distance(vertices.at(source_id), vertices.at(dest_id));
            Route r(source_id, dest_id, weight);
            return r;
        }
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
    airports_ = airports;
    for (Airport airport : airports) {
        //cout << airport.getAirportName() << endl;
        if (vertices.find(airport.getAirportID()) != vertices.end()) {
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
    vector<bool> labels(14110, false);

    q.push(sourceAP);
    labels[sourceAP] = true; // label sourceAP (starting point) as visited

    int currentAP = sourceAP; // copy of the input id
    labels[currentAP] = true;

    while (!(q.empty())) {
        currentAP = q.front();
        q.pop();

        ret.push_back(getAirportNameByID(currentAP));

        for (auto ap : adjacent(currentAP)) {
            if (labels[ap] == false) { // vertex is unexplored
                q.push(ap);
                labels[ap] = true;
            }
        }
    }
    return ret;
}

vector<string> Graph::traverseByDest(int sourceAP, int destAP) {
    vector<string> ret;
    queue<int> q;
    vector<bool> labels(14110+1, false);
    vector<int> pred(14110+1, -1);
    vector<int> distance(14110+1, INT_MAX);

    q.push(sourceAP);
    // labels[sourceAP] = true; // label sourceAP (starting point) as visited

    int currentAP = sourceAP; // copy of the input id
    labels[currentAP] = true;
    pred[currentAP] = -1;
    distance.push_back(currentAP);

    while (!(q.empty())) {
        currentAP = q.front();
        q.pop();
        cout << "The currentAP is: " << currentAP << endl;

        // check if we find the destination
        if (currentAP == destAP) {
            // cout << "a" << endl;
            break;
        }

        for (size_t i = 0; i < adjacent(currentAP).size(); i++) {
            if (labels[adjacent(currentAP)[i]] == false) { // vertex is unexplored
                q.push(adjacent(currentAP)[i]);
                labels[adjacent(currentAP)[i]] = true;
                distance[adjacent(currentAP)[i]] = distance[currentAP] + 1;
                pred[adjacent(currentAP)[i]] = currentAP;
            }
        }
    }
    // no path exsits
    if (currentAP != destAP) {
        return vector<string>();
    } 

    ret.push_back(getAirportNameByID(destAP));
    while (pred[currentAP] != -1) {
        cout << pred[currentAP] << endl;
        ret.push_back(getAirportNameByID(pred[currentAP]));
        currentAP = pred[currentAP];
    }
    cout << ret.size() << endl;

    reverse(ret.begin(), ret.end());

    for (string str : ret) {
        cout << str << endl;
    }
    return ret;
}


/************************************************
Dijkstras: find shortest path (recommended travel paths)
************************************************/

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
    //cout << "line 249" << endl;
    for (int i = 0; i < 14110; i++) {
        // find the node not visited and closest to the source
        //cout << "i = " << i << endl;
        int next;
        int min_dist = INT_MAX;
        for (int j = 0; j < 14110; j++) {
            if (!visited[j] && distance[j] < min_dist) {
                min_dist = distance[j];
                next = j;
            }
        }
        //cout << "line 261" << endl;

        visited[next] = true;
        // update distance and shortest path
        //cout << "line 265" << endl;
        vector<int> adjacents = adjacent(next); // problem "map::at"
        //cout << "line 267" << endl;
        for (int j : adjacents) {
            //cout << "j = " << j << endl;
            if (!visited[j]) {
                //cout << "line 271" << endl;
                int new_dist = getAdjDistance(next, j) + distance[next];
                //cout << "line 274" << endl;
                if (new_dist < distance[j]) {
                    distance[j] = new_dist;
                    previous[j] = next;
                }
            }
        }
        //cout << "line 280" << endl;
    
    }

    // return the shortest path from source airport to destination
    vector<int> shortest_path;
    int current = destination_airport_id;
    while (current != source_airport_id) {
        shortest_path.push_back(current);
        current = previous[current];
    }
    shortest_path.push_back(current);
    reverse(shortest_path.begin(), shortest_path.end());
    /*for (int airport : shortest_path) {
        cout << airport << " / ";
    }*/
    return shortest_path;
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