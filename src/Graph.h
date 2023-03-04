#ifndef RAILWAYMANAGER_GRAPH_H
#define RAILWAYMANAGER_GRAPH_H

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include "Station.h"
#include "Trip.h"

using namespace std;

class Graph {
public:
    void readFiles(const string &file1, const string &file2);

    const unordered_map<string, Station *> &getStations() const;

    void setStations(const unordered_map<string, Station *> &stations);

    const unordered_map<string, vector<Station *>> &getLines() const;

    void setLines(const unordered_map<string, vector<Station *>> &lines);

    int getSize() const;

    void setSize(int size);

    // Read the files and create the graph
    void printStations();

private:
    unordered_map<string, Station *> stations; //nodes
    unordered_map<string, vector<Station *>> lines; //edges

    int size{};

    void addStation(Station *pStation);

    Station *getStation(const string &basicString);

    void addLine(const string &basicString, Station *pStation);
};


#endif
