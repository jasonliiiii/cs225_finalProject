#include "route.h"

//default constructor
Route::Route() = default;

//constructor without given weight
Route::Route(int s, int d) {
    sourceAP = s;
    destinationAP = d; 
    weight = -1000;
}

//constructor with everything
Route::Route(int s, int d, double w) {
    sourceAP = s;
    destinationAP = d; 
    weight = w;
}

//getters
int Route::getSourceId() {
    return sourceAP;
}  

int Route::getDestId() {
    return destinationAP;
}

double Route::getWeight() {
    return weight;
}
       
//setters
void Route::setWeight(double w) {
    weight = w;
}

void Route::setSource(double s) {
    sourceAP = s;
}

void Route::setDestination(double d) {
    destinationAP = d;
}