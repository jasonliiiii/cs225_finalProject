#include "airport.h"

using namespace std;

// Constructors
Airport::Airport() = default;

// sample line:
// 507,"London Heathrow Airport","London","United Kingdom","LHR","EGLL",51.4706,-0.461941,83,0,"E","Europe/London","airport","OurAirports"
// id, name, city, country, IATA, ICAO, Latitude, Longitude, Altitude, Timezone, DST, Tz database, source
Airport::Airport(string &line) {
    string s = "";
    vector<string> information;

    for (size_t i = 0; i < line.size(); i++) {
        char c = line[i];
        bool quotation = false;

        // no quotation mark occurs
        if (quotation == false) {
            // if current char is ",", which means we reach the end of one piece of information
            // pushback string s and reset s;
            if (c == ',') {
                information.push_back(s);
                s = "";
            // if current char is the first half of quotation mark,  
            } else if (c == '"') {
                quotation = true;
            // regular char
            } else {
                s += c;
            }
        // quotation mark occurs
        } else {
            // if current char is the second half of quotation mark
            if (c == '"' && i < line.size() - 1) {
                // if the next char is still the first half of quotation mark 
                if (line[i+1] == '"') {
                    s += '"';
                    i++;
                } else {
                    quotation = false;
                }
            } else {
                s += c;
            }
        }
    }
    
    // notation: the invalid data is read into the variable and treated as a valid data
    // we will deal with it in later part
    // stoi returns the converted string as integer
    id_ = stoi(information[0], nullptr);
    name_ = information[1];
    city_ = information[2];
    country_ = information[3];
    // stod returns the converted floating point as double
    latitude_ = stod(information[6], nullptr);
    longitude_ = stod(information[7], nullptr);
}

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