#pragma once

class Route {
    public:
    // Constructors
    Route();
    Route(string source_airport, int source_airport_id, string destination_airport, int destination_airport_id);

    // getter
    int getSourceID();
    int getDestID();
    string getSourceName();
    string getDestName();

    // helper function to read data
    string& getline(string & routeFile);

    // read file from route.dat
    // returns a map with content: key: id of an airport, value: a set of ids of airports has routes
    map<int, set<int>> readRoutes(string &line);

    private:
    string source_airport_;
    int source_airport_id_;
    string destination_airport_;
    int destination_airport_id_;
};