#include "airport.h"

using namespace std;

// Constructors
Airport::Airport() = default;

Airport::Airport(int id, string name, string city, string country, double latitude, double longitude) {
    id_ = id;
    name_ = name;
    city_ = city;
    country_ = country;
    latitude_ = latitude;
    longitude_ = longitude;
}

// helper function to calculate distance
double Airport::radianConvert(double degress) {
    double pi = 22/7;
    return degress * (pi / 180);
}

// function to calculate distance between two ids of airports
double Airport::calculate_distance(Airport from, Airport dest) {
    double la1 = from.getAirportLatitude();
    double la2 = dest.getAirportLatitude();
    double lo1 = from.getAirportLongitude();
    double lo2 = dest.getAirportLongitude();
    la1 = radianConvert(la1);
    la2 = radianConvert(la2);
    lo1 = radianConvert(lo1);
    lo2 = radianConvert(lo2);
    // Haversine Formula
    double diff_lo = lo2 - lo1;
    double diff_la = la2 - la1;
    double to_return = pow(sin(diff_la / 2), 2) + cos(la1) * cos(la2) * pow(sin(diff_lo / 2), 2);
    to_return = 2 * asin(sqrt(to_return));
    // Radius of Earth in Kilometers, R = 6371
    double earth_radius = 6371;
    return to_return * earth_radius;
}