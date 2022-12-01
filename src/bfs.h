#pragma once
#include "airport.h"
#include "airport_graph.h"
#include <string>
#include <queue>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <iostream>


using namespace std;

class BFS{
    public:

    unordered_map<string, Node*> abbrMap();
    Node* abbr(string abbr);
    vector<string> shortestDist(string from, string dest);
    private:
    unordered_map<string, Node*> NodeMap;
}

