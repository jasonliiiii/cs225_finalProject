#include <catch2/catch_test_macros.hpp>
#include "airport.h"
#include "route.h"
#include "airport_graph.h"

using namespace std;

TEST_CASE("Check readLineAirport1", "[weight=1][timeout=30000]") {
  string line = "507,\"London Heathrow Airport\",\"London\",\"United Kingdom\",\"LHR\",\"EGLL\",51.4706,-0.461941,83,0,\"E\",\"Europe/London\",\"airport\",\"OurAirports\"";
  Airport airport = Airport(line);
  REQUIRE(airport.getAirportID() == 507);
  REQUIRE(airport.getAirportName() == "London Heathrow Airport");
  REQUIRE(airport.getAirportCity() == "London");
  REQUIRE(airport.getAirportCountry() == "United Kingdom");
  REQUIRE(airport.getAirportLatitude() == 51.4706);
  REQUIRE(airport.getAirportLongitude() == -0.461941);
}

TEST_CASE("Check readLineAirport2", "[weight=1][timeout=30000]") {
  string line = "104,\"Pitt Meadows Airport\",\"Pitt Meadows\",\"Canada\",\\N,\"CYPK\",49.21609878540039,-122.70999908447266,11,-8,\"A\",\"America/Vancouver\",\"airport\",\"OurAirports\"";
  Airport airport = Airport(line);
  REQUIRE(airport.getAirportID() == 104);
  REQUIRE(airport.getAirportName() == "Pitt Meadows Airport");
  REQUIRE(airport.getAirportCity() == "Pitt Meadows");
  REQUIRE(airport.getAirportCountry() == "Canada");
  REQUIRE(airport.getAirportLatitude() == 49.21609878540039);
  REQUIRE(airport.getAirportLongitude() == -122.70999908447266);
}

TEST_CASE("Check readLineRoute1", "[weight=1][timeout=30000]") {
  string line = "2B,410,AER,2965,KZN,2990,,0,CR2";
  Graph g;
  vector<string> parts = g.readLineRoute(line);
  REQUIRE(parts.size() == 8);
  REQUIRE(parts.at(2) == "AER");
  REQUIRE(parts.at(3) == "2965");
  REQUIRE(parts.at(4) == "KZN");
  REQUIRE(parts.at(5) == "2990");
  REQUIRE(parts.at(7) == "0");
}

TEST_CASE("Check readLineRoute2", "[weight=1][timeout=30000]") {
  string line = "2B,410,DME,4029,TGK,\\N,,0,CR2";
  Graph g;
  vector<string> parts = g.readLineRoute(line);
  REQUIRE(parts.empty() == true);
}

TEST_CASE("Calculate Distance", "[weight=1][timeout=30000") {
  Airport a1 = Airport(507, "London Heathrow Airport", "London", "United Kingdom", 51.4706, -0.461941);
  Airport a2 = Airport(26,"Kugaaruk Airport","Pelly Bay","Canada",68.534401,-89.808098);
  REQUIRE((int)a1.calculate_distance(a1,a2) == 4975);
}

TEST_CASE("Graph Construction1", "[weight=1][timeout=30000]") {
  Airport a1 = Airport(507, "London Heathrow Airport", "London", "United Kingdom", 51.4706, -0.461941);
  Airport a2 = Airport(26,"Kugaaruk Airport","Pelly Bay","Canada",68.534401,-89.808098);
  Airport a3 = Airport(3127,"Pokhara Airport","Pokhara","Nepal",28.200899124145508,83.98210144042969);
  Airport a4 = Airport(8810,"Hamburg Hbf","Hamburg","Germany",53.552776,10.006683);
  vector<Airport> airports = {a1, a2, a3, a4};
  Graph g = Graph();
  g.setVerticesMap(airports);
  REQUIRE(g.getAirportNameByID(507) == "London Heathrow Airport");
  REQUIRE(g.getAirportNameByID(26) == "Kugaaruk Airport");
  REQUIRE(g.getAirportNameByID(3127) == "Pokhara Airport");
  REQUIRE(g.getAirportNameByID(8810) == "Hamburg Hbf");
}

TEST_CASE("Graph Construction2", "[weight=1][timeout=30000]") {
  Route r1 = Route(1, 2, 10); //id = 1, connected to 2
  Route r2 = Route(1, 3, 20); 
  Route r3 = Route(1, 4, 40); 
  vector<Route> routes = {r1, r2, r3};
  Graph g = Graph();
  g.setRelationMap(routes);
  vector<int> adjacents = g.adjacent(1); 
  REQUIRE(adjacents.size() == 3);
  REQUIRE(adjacents.at(0) == 2);
  REQUIRE(adjacents.at(1) == 3);
  REQUIRE(adjacents.at(2) == 4);
}

TEST_CASE("BFS", "[weight=1][timeout=30000]") {
  Airport a1 = Airport(507, "London Heathrow Airport", "London", "United Kingdom", 51.4706, -0.461941);
  Airport a2 = Airport(26,"Kugaaruk Airport","Pelly Bay","Canada",68.534401,-89.808098);
  Airport a3 = Airport(3127,"Pokhara Airport","Pokhara","Nepal",28.200899124145508,83.98210144042969);
  Airport a4 = Airport(8810,"Hamburg Hbf","Hamburg","Germany",53.552776,10.006683);
  vector<Airport> airports = {a1, a2, a3, a4};
  Graph g = Graph();
  g.setVerticesMap(airports);
  Route r1 = Route(507, 26, 1000);
  Route r2 = Route(26, 3127, 1300);
  Route r3 = Route(507, 8810, 3200);
  vector<Route> routes = {r1, r2, r3};
  g.setRelationMap(routes);
  vector<string> path = g.traverseByDest(507, 3127);
  REQUIRE(path.size() == 3);
  REQUIRE(path.at(0) == "London Heathrow Airport");
  REQUIRE(path.at(1) == "Kugaaruk Airport");
  REQUIRE(path.at(2) == "Pokhara Airport");
}

TEST_CASE("Find shortest path by distance", "[weight=1][timeout=30000]") {
  Airport a1 = Airport(507, "London Heathrow Airport", "London", "United Kingdom", 51.4706, -0.461941);
  Airport a2 = Airport(26,"Kugaaruk Airport","Pelly Bay","Canada",68.534401,-89.808098);
  Airport a3 = Airport(3127,"Pokhara Airport","Pokhara","Nepal",28.200899124145508,83.98210144042969);
  Airport a4 = Airport(8810,"Hamburg Hbf","Hamburg","Germany",53.552776,10.006683);
  vector<Airport> airports = {a1, a2, a3, a4};
  Graph g = Graph();
  Route r1 = Route(507, 26, 1000); // a1 -> a2 by distance 1000
  Route r2 = Route(26, 3127, 100); // a2 -> a3 by distance 100
  Route r3 = Route(507, 8810, 2000); // a1 -> a4 by distance 2000
  Route r4 = Route(8810, 3127, 1000); // a3 -> a4 by distance 1000
  vector<Route> routes = {r1, r2, r3, r4};
  g.setRelationMap(routes);
  vector<int> path = g.dijkstras(507, 3127);
  REQUIRE(path.size() == 3);
  REQUIRE(path.at(0) == 507);
  REQUIRE(path.at(1) == 26);
  REQUIRE(path.at(2) == 3127);
}

TEST_CASE("Find strongly connected component", "[weight=1][timeout=30000]") {
  Airport a1 = Airport(507, "London Heathrow Airport", "London", "United Kingdom", 51.4706, -0.461941);
  Airport a2 = Airport(26,"Kugaaruk Airport","Pelly Bay","Canada",68.534401,-89.808098);
  Airport a3 = Airport(3127,"Pokhara Airport","Pokhara","Nepal",28.200899124145508,83.98210144042969);
  Airport a4 = Airport(8810,"Hamburg Hbf","Hamburg","Germany",53.552776,10.006683);
  vector<Airport> airports = {a1, a2, a3, a4};
  Graph g = Graph();
  Route r1 = Route(507, 26, 1000); // a1 -> a2
  Route r2 = Route(26, 3127, 100); // a2 -> a3 
  Route r3 = Route(3127, 507, 2000); // a3 -> a1 --> stongly connected!
  Route r4 = Route(26, 8810, 1000); // a2 -> a4
  vector<Route> routes = {r1, r2, r3, r4};
  g.setRelationMap(routes);
  vector<int> path = g.kosaraju(507);
  REQUIRE(path.size() == 3);
  REQUIRE(path.at(0) == 507);
  REQUIRE(path.at(1) == 26);
  REQUIRE(path.at(2) == 3127);
}