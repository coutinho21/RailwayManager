#include "StationTrip.h"


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

void Station::addEdge(Station *destination, int capacity, const string &service) {
    Trip *trip = new Trip(this, destination, capacity, service);
    trips.push_back(trip);
}

const vector<Trip *> &Station::getTrips() const {
    return trips;
}

void Station::setTrips(const vector<Trip *> &trips) {
    Station::trips = trips;
}

bool Station::isVisited() const {
    return visited;
}

void Station::setVisited(bool visited) {
    Station::visited = visited;
}

void Station::printConnections() {
    cout << "\nStation: " << name << endl;
    for (auto &trip : trips) {
        cout << "\tDestination: " << trip->getDestination()->getName() << " - Capacity: " << trip->getCapacity() << " - Service: "
             << trip->getService() << endl;
    }
    cout << "\n";
}

Trip *Station::getPath() const {
    return path;
}

void Station::setPath(Trip *path) {
    Station::path = path;
}

const vector<Trip *> &Station::getIncoming() const {
    return incoming;
}


//*********//

Trip::Trip(Station *source, Station *destination, int capacity, const string& service) {
    this->source = source;
    this->destination = destination;
    this->capacity = capacity;
    this->service = service;
}

Station *Trip::getSource() const {
    return source;
}

void Trip::setSource(Station* source) {
    Trip::source = source;
}

Station *Trip::getDestination() const {
    return destination;
}

void Trip::setDestination(Station* destination) {
    Trip::destination = destination;
}

int Trip::getCapacity() const {
    return capacity;
}

void Trip::setCapacity(int capacity) {
    Trip::capacity = capacity;
}

const string &Trip::getService() const {
    return service;
}

void Trip::setService(const string &service) {
    Trip::service = service;
}

int Trip::getFlow() const {
    return flow;
}

void Trip::setFlow(int flow) {
    Trip::flow = flow;
}

Trip *Trip::getReverse() const {
    return reverse;
}

void Trip::setReverse(Trip *reverse) {
    Trip::reverse = reverse;
}