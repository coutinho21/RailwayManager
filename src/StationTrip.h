#ifndef RAILWAYMANAGER_STATIONTRIP_H
#define RAILWAYMANAGER_STATIONTRIP_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Trip;

// Station class represents the nodes of the graph

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

    void addEdge(Station *destination, int capacity, const string &service);

    const vector<Trip *> &getTrips() const;

    void setTrips(const vector<Trip *> &trips);

    bool isVisited() const;

    void setVisited(bool visited);

    void printConnections();

    Trip *getPath() const;

    void setPath(Trip *path);

    const vector<Trip *> &getIncoming() const;

    void setIncoming(const vector<Trip *> &incoming);

private:
    string name, district, municipality, township, line;
    vector<Trip *> trips; // edges of the graph
    bool visited = false;
    Trip *path = nullptr;
    vector<Trip *> incoming;

};


// Trip class represents the edges of the graph

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

    int getFlow() const;

    void setFlow(int flow);

    Trip *getReverse() const;

    void setReverse(Trip *reverse);

private:
    Station *source;
    Station *destination;
    int capacity;
    int flow = 0;
    string service;
    Trip *reverse = nullptr;
};


#endif