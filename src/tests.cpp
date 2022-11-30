#include <catch2/catch_test_macros.hpp>
#include "/workspaces/cs225/release-f22/final_project/src/airport.h"
#include "/workspaces/cs225/release-f22/final_project/src/route.h"
//#include "Catch2/catch.hpp"

using namespace std;

TEST_CASE("Check Airport constructor", "[weight=1][timeout=30000]") {
  string line = " 507,\"London Heathrow Airport\",\"London\",\"United Kingdom\",\"LHR\",\"EGLL\",51.4706,-0.461941,83,0,\"E\",\"Europe/London\",\"airport\",\"OurAirports\"";
  Airport airport = Airport(line);
  REQUIRE(airport.getAirportID() == 507);
  REQUIRE(airport.getAirportName() == "London Heathrow Airport");
  REQUIRE(airport.getAirportCity() == "London");
  REQUIRE(airport.getAirportCountry() == "United Kingdom");
  REQUIRE(airport.getAirportLatitude() == 51.4706);
  REQUIRE(airport.getAirportLongitude() == -0.461941);
}

