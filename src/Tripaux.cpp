
#include "Tripaux.h"

Tripaux::Tripaux(Station *source, Station *destination, int capacity, int cost, int rev) {
    this->source = source;
    this->destination = destination;
    this->capacity = capacity;
    this->cost = cost;
    this->rev = rev;
}

Station *Tripaux::getSource() const {
    return source;
}

void Tripaux::setSource(Station *source) {
    Tripaux::source = source;
}

Station *Tripaux::getDestination() const {
    return destination;
}

void Tripaux::setDestination(Station *destination) {
    Tripaux::destination = destination;
}

int Tripaux::getCapacity() const {
    return capacity;
}

void Tripaux::setCapacity(int capacity) {
    Tripaux::capacity = capacity;
}

int Tripaux::getCost() const {
    return cost;
}

void Tripaux::setCost(int cost) {
    Tripaux::cost = cost;
}

int Tripaux::getRev() const {
    return rev;
}

void Tripaux::setRev(int rev) {
    Tripaux::rev = rev;
}
