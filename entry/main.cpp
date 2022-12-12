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
    //cout << "The size of the vertext is: " << m.size() << endl;
    map<int, set<pair<int,double>>> r = airport_web.getRelatedAirports();
    //cout << "The size of the related map is: " << r.size() << endl;
    cout << "--------------------------------------------------------------------------------------------------" << endl;
    cout << "*****                       Welcome to the Airport Search!                                   *****" <<endl;
	cout << "*****  - Enter 1 to find the shortest path between two airports (least number of transfers)  *****" << endl;
	cout << "*****  - Enter 2 to find the shortest path between two airports (shotest distance)           *****" << endl;
    cout << "*****  - Enter 3 to find the airports that are strongly connected to the given airport       *****" << endl;
	cout << "--------------------------------------------------------------------------------------------------" << endl;
    cout << "Please enter your option: " << endl;
    int option = 0;
    cin >> option;
    if (option == 1) {
        cout << "Please enter the starting airport id: " << endl;
        int starting_id; 
        cin >> starting_id;
        cout << "Please enter the destination airport id: " << endl;
        int dest_id;
        cin >> dest_id;
        //vector<string> airports = airport_web.traverseByDest(starting_id, dest_id);
        vector<string> airports = airport_web.traverseByDest(starting_id, dest_id);
        cout << "Output: " << endl; 
        for (string i : airports) {
            cout << i << " --> ";
        }
        cout << "Destination Arrived";
        cout << endl;
    } else if (option == 2) {
        cout << "Please enter the starting airport id: " << endl;
        int starting_id; 
        cin >> starting_id;
        cout << "Please enter the destination airport id: " << endl;
        int dest_id;
        cin >> dest_id; 
        vector<int> airports = airport_web.dijkstras(starting_id, dest_id);
        cout << "Output: " << endl; 
        for (int i : airports) {
            cout << m[i].getAirportName() << " --> ";
        }
        cout << "Destination Arrived!";
        cout << endl;
    } else {
        cout << "Please enter the starting airport id: " << endl;
        int starting_id; 
        cin >> starting_id;
        vector<int> airports = airport_web.kosaraju(starting_id);
        cout << "Output: " << endl; 
        for (int i : airports) {
            cout << m[i].getAirportName() << " ";
        }
        cout << endl;
    }
    return 0;
}