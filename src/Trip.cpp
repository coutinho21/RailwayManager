#include "Trip.h"

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

Trip::Trip(Station *source, Station *destination, int capacity, const string& service) {
    this->source = source;
    this->destination = destination;
    this->capacity = capacity;
    this->service = service;

}


