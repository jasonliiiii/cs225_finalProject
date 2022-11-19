#pragma once
#include "airport_graph.h"
#include "airport.h"
#include "route.h"

#include <vector>
#include <map>
#include <queue>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

class Dijkstras {
    public:
    Dijkstras(Graph graph, int source_airport_id, int destination_airport_id);
    Dijkstras(Graph graph, string source_airport, string destination_airport);

    private:
}