#include "Station.h"

const string &Station::getName() const {
    return name;
}

void Station::setName(const string &name) {
    Station::name = name;
}

const string &Station::getDistrict() const {
    return district;
}

void Station::setDistrict(const string &district) {
    Station::district = district;
}

const string &Station::getMunicipality() const {
    return municipality;
}

void Station::setMunicipality(const string &municipality) {
    Station::municipality = municipality;
}

const string &Station::getTownship() const {
    return township;
}

void Station::setTownship(const string &township) {
    Station::township = township;
}

const string &Station::getLine() const {
    return line;
}

void Station::setLine(const string &line) {
    Station::line = line;
}

Station::Station(const string &name, const string &district, const string &municipality, const string &township,
                 const string &line) {
    this->name = name;
    this->district = district;
    this->municipality = municipality;
    this->township = township;
    this->line = line;
}
