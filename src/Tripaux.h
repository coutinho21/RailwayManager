

#ifndef RAILWAYMANAGER_TRIPAUX_H
#define RAILWAYMANAGER_TRIPAUX_H


#include "StationTrip.h"

class Tripaux {

public:
    int capacity;
    Tripaux(Station *source, Station *destination, int capacity, int cost, int rev);

    Station *getSource() const;

    void setSource(Station *source);

    Station *getDestination() const;

    void setDestination(Station *destination);

    int getCapacity() const;

    void setCapacity(int capacity);

    int getCost() const;

    void setCost(int cost);

    int getRev() const;

    void setRev(int rev);

private:
    Station *source;
    Station *destination;
    int cost;
    int rev;
};


#endif //RAILWAYMANAGER_TRIPAUX_H
