#ifndef RAILWAYMANAGER_TRIP_H
#define RAILWAYMANAGER_TRIP_H


#include "Station.h"
#include <string>

using namespace std;

class Trip {
public:

    Trip(Station *source, Station *destination, int capacity, const string &service);

    Station *getSource() const;

    void setSource(Station *source);

    Station *getDestination() const;

    void setDestination(Station *destination);

    int getCapacity() const;

    void setCapacity(int capacity);

    const string &getService() const;

    void setService(const string &service);

private:
    Station *source;
    Station *destination;
    int capacity;
    string service;
};


#endif
