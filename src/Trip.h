#ifndef RAILWAYMANAGER_TRIP_H
#define RAILWAYMANAGER_TRIP_H


#include "Station.h"

class Trip {
public:

    Trip(Station *source, Station *destination, int capacity, string service);

    Station *getSource() const;

    void setSource(const Station &source);

    Station *getDestination() const;

    void setDestination(const Station &destination);

    int getCapacity() const;

    void setCapacity(int capacity);

    const string &getService() const;

    void setService(const string &service);

private:
    Station source, destination;
    int capacity;
    string service;
};


#endif //RAILWAYMANAGER_TRIP_H
