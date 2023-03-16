#include "Graph.h"

void Graph::readFiles(const string &file1, const string &file2) {
    ifstream stationsFile, linesFile;
    string line;

    stationsFile.open(file1);
    linesFile.open(file2);

    std::getline(stationsFile, line, '\n'); //step var names ahead
    std::getline(linesFile, line, '\n');  //step var names ahead

    if (stationsFile.is_open()) {
        while (std::getline(stationsFile, line, '\n')) {
            istringstream iss(line);
            vector<string> temp;
            string name, district, municipality, township, lineName, tempstr;
            while ((std::getline(iss, tempstr, ','))) {
                if (!tempstr.empty() && tempstr[tempstr.size() - 1] == '\r')
                    tempstr.erase(tempstr.size() - 1);
                temp.push_back(tempstr);
            }
            auto *s = new Station(temp[0], temp[1], temp[2], temp[3], temp[4]);
            this->addStation(s);

        }
        stationsFile.close();
    } else
        cout << "Unable to open file" << endl;

/*
    if (linesFile.is_open()) {
        while (getline(linesFile, line, ',')) {
            istringstream iss(line);
            string stringStationA, stringStationB, capacity, service;
            iss >> stringStationA >> stringStationB >> capacity >> service;
            Station *stationA = this->getStation(stringStationA);
            Station *stationB = this->getStation(stringStationB);
            // Trip *s = new Trip(stationA, stationB, stoi(capacity), service);    // nao me lembro para que era isto???
            this->addLine(stationA->getLine(), stationA);
        }
        linesFile.close();
    } else
        cout << "Unable to open file" << endl;
*/
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

unordered_map<string, Station *> &Graph::getStations(){
    return stations;
}

void Graph::setStations(const unordered_map<string, Station *> &stations) {
    Graph::stations = stations;
}

unordered_map<string, vector<Station *>> &Graph::getLines(){
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
    for (auto &station: this->stations)
        cout << station.second->getName() << ' ' << station.second->getDistrict() <<
        ' ' << station.second->getMunicipality() << ' ' << station.second->getTownship() <<
        ' ' << station.second->getLine() << endl;
}
