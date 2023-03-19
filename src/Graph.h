#ifndef RAILWAYMANAGER_GRAPH_H
#define RAILWAYMANAGER_GRAPH_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
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

    void addLine(const string &basicString, Station *pStation);

    void printConnectionsTo(const string& stationName);

    void dijkstra(const string& source, const string& destination);

private:
    unordered_map<string, Station *> stations; // nodes of the graph
    unordered_map<string, vector<Station *>> lines; // lines of the trains

    int size{};
};


#endif
