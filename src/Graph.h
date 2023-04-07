#ifndef RAILWAYMANAGER_GRAPH_H
#define RAILWAYMANAGER_GRAPH_H

#include <algorithm>
#include <fstream>
#include <sstream>
#include <queue>
#include <unordered_map>
#include "StationTrip.h"

using namespace std;

// Graph class represents a directed graph

class Graph {
public:
    void readFiles(const string &file1, const string &file2);

    unordered_map<string, Station *> &getStations();

    void setStations(const unordered_map<string, Station *> &stations);

    unordered_map<string, vector<Station *>> &getLines();

    void setLines(const unordered_map<string, vector<Station *>> &lines);

    int getSize() const;

    void setSize(int size);

    // Read the files and create the graph
    void printStations();

    void printAllConnections();

    void addStation(Station *pStation);

    Station *getStation(const string &basicString);

    void addEdge(Station *source, Station *destination, int capacity, const string &service);

    void removeEdge(Station *source, Station *destination);

    void addLine(const string &basicString, Station *pStation);

    void printConnectionsTo(const string& stationName);

    void dijkstra(const string& source, const string& destination);

    Station *findStation(const string& source);

    bool bfskarp(const string& source, const string& target);

    int maxFlow(const string &source, const string &destination);

    void maxMaxFlow();

    void maxFlowDistrict(int k);

    void maxFlowMunicipality(int k);

    int maxTrainsArrival(const string& station);

    void minCostMaxFlow(const string& source, const string& destination);

private:
    unordered_map<string, Station *> stations; // nodes of the graph
    unordered_map<string, vector<Station *>> lines; // lines of the trains
    int size{};


};


#endif