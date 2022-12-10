#pragma once

#include <vector>
#include <set>
#include <map>

#include <string>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <math.h>


#include "route.h"

using namespace std;

class Airport {
    public:
    // constructor
    Airport();
    //Airport(string &line);
    Airport(int id, string name, string city, string country, double latitude, double longitude);

    // setters
    void setAirportID(int id) {id_ = id;}
    void setAirportName(string name) {name_ = name;}
    void setAirportCity(string city) {city_ = city;}
    void setAirportCountry(string country) {country_ = country;}
    void setAirportLatitude(double latitude) {latitude_ = latitude;}
    void setAirportLongitude(double longtitude) {longitude_ = longtitude;}

    // getters
    int getAirportID() {return id_;}
    string getAirportName() {return name_;}
    string getAirportCity() {return city_;}
    string getAirportCountry() {return country_;}
    double getAirportLatitude() {return latitude_;}
    double getAirportLongitude() {return longitude_;}

    // helper function to calculate distance
    double radianConvert(double degress);

    // function to calculate distance between two airports
    double calculate_distance(Airport from, Airport dest);

    private:
    int id_;
    string name_;
    string city_;
    string country_;
    double latitude_;
    double longitude_;
};