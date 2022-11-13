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
        bool quotation;

        // no quotation mark occurs
        if (quotation == false) {
            // if current char is ",", which means we reach the end of one piece of information
            // pushback string s and reset s;
            if (c == ",") {
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