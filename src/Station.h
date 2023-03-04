#ifndef RAILWAYMANAGER_STATION_H
#define RAILWAYMANAGER_STATION_H

#include <string>
#include <vector>
#include "Trip.h"

using namespace std;

class Station {
public:
    Station(const string &name, const string &district, const string &municipality, const string &township,
            const string &line);

    const string &getName() const;

    void setName(const string &name);

    const string &getDistrict() const;

    void setDistrict(const string &district);

    const string &getMunicipality() const;

    void setMunicipality(const string &municipality);

    const string &getTownship() const;

    void setTownship(const string &township);

    const string &getLine() const;

    void setLine(const string &line);

private:
    string name, district, municipality, township, line;
    vector<Trip *> trips;
};


#endif
