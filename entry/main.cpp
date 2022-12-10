#include <iostream>
#include <vector>
#include <unordered_map>
#include <iomanip>

#include "airport.h"
#include "airport_graph.h"
#include "route.h"

using namespace std;

int main() {
    Graph airport_web = Graph("/workspaces/cs225/release-f22/final_project/src/airports.dat.txt", 
    "/workspaces/cs225/release-f22/final_project/src/routes.dat.txt");
    map<int, Airport> m = airport_web.getVertices();
    cout << "The size of the vertext is: " << m.size() << endl;
    map<int, set<pair<int,double>>> r = airport_web.getRelatedAirports();
    cout << "The size of the related map is: " << r.size() << endl;
}