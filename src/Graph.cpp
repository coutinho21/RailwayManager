#include "Graph.h"

void Graph::readFiles(const string &file1, const string &file2) {
    ifstream stationsFile, linesFile;
    string line;

    stationsFile.open(file1);
    linesFile.open(file2);

    std::getline(stationsFile, line, '\n'); //step var names ahead
    std::getline(linesFile, line, '\n');  //step var names ahead

    if (stationsFile.is_open()) {
        cout << "File opened" << endl;
        while (getline(stationsFile, line)) {
            istringstream iss(line);
            string name, district, municipality, township, lineName;
            iss >> name >> district >> municipality >> township >> lineName;
            auto *s = new Station(name, district, municipality, township, lineName);
            this->addStation(s);
        }
        cout << "File closed" << endl;
        stationsFile.close();
    } else {
        cout << "Unable to open file" << endl;
    }
    if (linesFile.is_open()) {
        while (getline(linesFile, line)) {
            istringstream iss(line);
            string stringStationA, stringStationB, capacity, service;
            iss >> stringStationA >> stringStationB >> capacity >> service;
            Station *stationA = this->getStation(stringStationA);
            Station *stationB = this->getStation(stringStationB);
            Trip *s = new Trip(stationA, stationB, stoi(capacity), service);
            this->addLine(lineName, s);
        }
        linesFile.close();
    } else {
        cout << "Unable to open file" << endl;
    }
    cout << "END" << endl;
}

void Graph::addStation(Station *pStation) {
    stations[pStation->getName()] = pStation;
    size++;
}

Station *Graph::getStation(const string &basicString) {
    return stations[basicString];
}

void Graph::addLine(const string &basicString, Station *pStation) {
    lines[basicString].push_back(pStation);
}

const unordered_map<string, Station *> &Graph::getStations() const {
    return stations;
}

void Graph::setStations(const unordered_map<string, Station *> &stations) {
    Graph::stations = stations;
}

const unordered_map<string, vector<Station *>> &Graph::getLines() const {
    return lines;
}

void Graph::setLines(const unordered_map<string, vector<Station *>> &lines) {
    Graph::lines = lines;
}

int Graph::getSize() const {
    return size;
}

void Graph::setSize(int size) {
    Graph::size = size;
}

void Graph::printStations() {
    cout << "HERE" << endl;
    for (auto &station: this->stations)
        cout << station.first << endl;
    cout << "ALSO HERE" << endl;
}
