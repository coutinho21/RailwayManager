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
            string tempstr;
            while ((std::getline(iss, tempstr, ','))) {
                if (!tempstr.empty() && tempstr[tempstr.size() - 1] == '\r')
                    tempstr.erase(tempstr.size() - 1);

                // Check if the current value starts with a double quote
                if (tempstr.front() == '\"') {
                    if(tempstr.back() == '\"') {
                        tempstr.erase(remove(tempstr.begin(), tempstr.end(), '\"'), tempstr.end());
                        temp.push_back(tempstr);
                        continue;
                    }
                    // If it does, continue reading from the input stream until
                    // we encounter another double quote
                    string quotedString = tempstr;
                    while (std::getline(iss, tempstr, ',') && tempstr.back() != '\"') {
                        quotedString += ',' + tempstr;
                    }
                    quotedString += ',' + tempstr;

                    // Remove the double quotes from the resulting string
                    quotedString.erase(remove(quotedString.begin(), quotedString.end(), '\"'), quotedString.end());

                    tempstr = quotedString;
                }

                temp.push_back(tempstr);
            }
            auto *s = new Station(temp[0], temp[1], temp[2], temp[3], temp[4]);
            this->addStation(s);
        }


        stationsFile.close();
    } else
        cout << "Unable to open file" << endl;


    if (linesFile.is_open()) {
        while (std::getline(linesFile, line, '\n')) {
            istringstream iss(line);
            vector<string> temp;
            string stringStationA, stringStationB, capacity, service, tempstr;
            while ((std::getline(iss, tempstr, ','))) {
                if (!tempstr.empty() && tempstr[tempstr.size() - 1] == '\r')
                    tempstr.erase(tempstr.size() - 1);
                if (tempstr.size() >= 2 && tempstr[0] == '"' && tempstr[tempstr.size() - 1] == '"')
                    tempstr = tempstr.substr(1, tempstr.size() - 2);

                temp.push_back(tempstr);
            }
            Station *stationA = this->getStation(temp[0]);
            Station *stationB = this->getStation(temp[1]);
            this->addEdge(stationA, stationB, stoi(temp[2]), temp[3]);
            this->addLine(stationA->getLine(), stationA);
        }
        linesFile.close();
    } else
        cout << "Unable to open file" << endl;

}

void Graph::addStation(Station *pStation) {
    if( stations.find(pStation->getName()) == stations.end()) {
        stations[pStation->getName()] = pStation;
        size++;
    }
}

Station *Graph::getStation(const string &basicString) {
    return stations[basicString];
}

void Graph::addEdge(Station *source, Station *destination, int capacity, const string &service) {
    source->addEdge(destination, capacity, service);
    destination->addEdge(source, capacity, service);
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
