#pragma once
#include "airport_graph.h"
#include <string>
#include <queue>
#include <stack>
#include <map>
#include <fstream>
#include <vector>

using namespace std;

class BFS {
    public:
    BFS(string &airportFile, string &routeFile);

    // input : Graph G, output: A labeling of the edges on G as discovery and cross edge represented by vector
    vector<string> traverseAll(int sourceAP);

    vector<string> traverseByDest(int sourceAP, int destAP);
    
    private:
    Graph graph_;
};