#include "bfs.h"

using namespace std;

BFS::BFS(string &airportFile, string &routeFile) {
    graph_ = Graph(airportFile, routeFile);
}

vector<string> BFS::traverseAll(int sourceAP) {
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
        ret.push_back(graph_.getAirportNameByID(currentAP));

        for (auto ap : graph_.adjacent(currentAP)) {
            if (labels[ap] == false) { // vertex is unexplored
                labels[ap] = true;
                q.push(ap);
            }
        }
        q.pop();
    }
    return ret;
}

vector<string> BFS::traverseByDest(int sourceAP, int destAP) {
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
            ret.push_back(graph_.getAirportNameByID(currentAP));
        }

        ret.push_back(graph_.getAirportNameByID(currentAP));

        for (auto ap : graph_.adjacent(sourceAP)) {
            if (labels[ap] == false) { // vertex is unexplored
                labels[ap] = true;
                q.push(ap);
            }
        }
        q.pop();
    }
    return ret;
}