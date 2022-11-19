#pragma once

class Route {
    public:
        //default constructor
        Route();
        //constructor without given weight
        Route(int s, int d);
        //constructor with everything
        Route(int s, int d, double w);

        //getters
        int getSourceId();       
        int getDestId();         
        double getWeight();
       
        //setters
        void setWeight(double w);
        void setSource(double s);
        void setDestination(double d); 
    
    private:
        //source airport ID
        int sourceAP;
        //destination airport ID
        int destinationAP;
        //distances in KM between two airports
        double weight;
};