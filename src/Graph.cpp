#include "Graph.h"


void Graph::readFiles(const string &file1, const string &file2) {
    ifstream stationsFile, linesFile;
    string line;

    stationsFile.open(file1);
    linesFile.open(file2);

    getline(stationsFile, line, '\n'); //step var names ahead
    getline(linesFile, line, '\n');  //step var names ahead

    if (stationsFile.is_open()) {
        while (getline(stationsFile, line, '\n')) {
            istringstream iss(line);
            vector<string> temp;
            string tempstr;
            while ((getline(iss, tempstr, ','))) {
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
                    while (getline(iss, tempstr, ',') && tempstr.back() != '\"')
                        quotedString += ',' + tempstr;

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
    } else cout << "Unable to open file" << endl;


    if (linesFile.is_open()) {
        while (getline(linesFile, line, '\n')) {
            istringstream iss(line);
            vector<string> temp;
            string stringStationA, stringStationB, capacity, service, tempstr;
            while ((getline(iss, tempstr, ','))) {
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
    } else cout << "Unable to open file" << endl;
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
    cout << "\nAll stations:" << endl;
    for (auto &station: this->stations)
        cout << "\tStation name -> " << station.second->getName() << endl
        << "\tStation district -> " << station.second->getDistrict() << endl
        << "\tStation municipality -> " << station.second->getMunicipality() << endl
        << "\tStation township -> " << station.second->getTownship() << endl
        << "\tStation line -> " << station.second->getLine() << endl << "\n\n";
}

void Graph::printAllConnections() {
    cout << "\nAll connections:" << endl;
    for (auto &station: this->stations)
        station.second->printConnections();
}

void Graph::printConnectionsTo(const string& stationName) {
    cout << "\nConnections to " << stationName << ':' << endl;
    for(auto &station: this->stations){
        for(auto &connection: station.second->getTrips()){
            if(connection->getDestination()->getName() == stationName)
                cout << '\t' << station.second->getName() << " -> " << connection->getDestination()->getName() << endl;
        }
    }

}

void Graph::dijkstra(const string &source, const string &destination) {
    unordered_map<string, Station*> visited;
    unordered_map<string, Station*> unvisited;
    unordered_map<string, Station*> previous;
    unordered_map<string, int> distance;
    int sf = 1;
    int df = 1;


    for(auto &station: stations){
        distance[station.first] = INT_MAX;
        unvisited[station.first] = station.second;

        if(station.first == source) sf = 0;
        if(station.first == destination) df = 0;
    }

    if(sf){
        cout << "Invalid Source Station Name.\n";
        return;
    }
    if(df){
        cout << "Invalid Destination Station Name.\n";
        return;
    }

    distance[source] = 0;

    while(!unvisited.empty()){
        Station* current = unvisited.begin()->second;
        for(auto &station: unvisited){
            if(distance[station.first] < distance[current->getName()])
                current = station.second;
        }

        if(current->getName() == destination)
            break;


        unvisited.erase(current->getName());
        visited[current->getName()] = current;

        for(auto &connection: current->getTrips()){
            if(visited.find(connection->getDestination()->getName()) == visited.end()){
                int alt = distance[current->getName()] + 1;
                if(alt < distance[connection->getDestination()->getName()]){
                    distance[connection->getDestination()->getName()] = alt;
                    previous[connection->getDestination()->getName()] = current;
                }
            }
        }
    }

    vector<string> path;
    Station* current = stations[destination];
    while(current != nullptr){
        path.push_back(current->getName());
        current = previous[current->getName()];
    }

    if(path[path.size()-1] != source){
        cout << "\nThere is no path from " << source << " to " << destination << endl;
        return;
    }

    cout << "\nShortest path from " << source << " to " << destination << " is:" << endl << "\n";
    for(int i = path.size() - 1; i >= 0; i--)
        cout << path[i] << (i == 0 ? "" : " -> ");
    cout << endl;
}

Station *Graph::findStation(const string& source) {
    for(const auto& station : stations){
        if(station.first == source){
            return station.second;
        }
    }
    return nullptr;
}


bool Graph::bfskarp(const string& source, const string& destination){
    std::queue<Station *> q;
    for(auto station : stations){
        station.second->setVisited(false);
        station.second->setPath(nullptr);
        for(auto e : station.second->getTrips()){
            delete e->getReverse();
            e->setReverse(nullptr);
        }
    }
    q.push(findStation(source));
    q.front()->setVisited(true);
    while(!q.empty()){
        auto v = q.front();
        q.pop();
        for(auto e : v->getTrips()){
            auto w = e->getDestination();
            if(!w->isVisited() && e->getCapacity() - e->getFlow() > 0){
                w->setPath(e);
                w->setVisited(true);
                q.push(w);
                if(w->getName() == destination) return true;
            }
        }
        for(auto e : v->getIncoming()){
            auto w = e->getSource();
            if(!w->isVisited() && e->getFlow() != 0){
                Trip* er = new Trip(e->getDestination(), e->getSource(), e->getFlow(), e->getService());
                er->setFlow(0);
                e->setReverse(er);
                er->setReverse(e);
                w->setVisited(true);
                w->setPath(er);
                q.push(w);
            }
        }
    }
    return false;
}


int Graph::maxFlow(const string &source, const string &destination){
    int sf = 1;
    int df = 1;

    for(const auto& station : stations){
        for(auto trip : station.second->getTrips())
            trip->setFlow(0);

        if(station.first == source) sf = 0;
        if(station.first == destination) df = 0;
    }

    if(sf){
        cout << "Invalid Source Station Name.\n";
        cout << source << endl;
        return 0;
    }
    if(df){
        cout << "Invalid Destination Station Name.\n";
        return 0;
    }

    int total_flow = 0;
    while(bfskarp(source, destination)){
        int mrc = INT32_MAX;
        auto e = findStation(destination)->getPath();
        while(true){
            if(e->getReverse()== nullptr && e->getCapacity() - e->getFlow() < mrc) mrc = e->getCapacity() - e->getFlow();
            if(e->getReverse()!= nullptr && e->getReverse()->getFlow() < mrc) mrc = e->getReverse()->getFlow();
            if(e->getSource()->getName() == source) break;
            e = e->getSource()->getPath();
        }
        e = findStation(destination)->getPath();
        while(true){
            if(e->getReverse() != nullptr)
                e->getReverse()->setFlow(e->getReverse()->getFlow() - mrc);
            else
                e->setFlow(e->getFlow() + mrc);

            if(e->getSource()->getName() == source) break;
            e = e->getSource()->getPath();
        }
        total_flow += mrc;
    }
    return total_flow;
}

void Graph::MaxMaxFlow() {
    int res = 0;
    int temp = 0;
    unordered_map<string, int> st_temp;
    unordered_map<string, Station *> auxStations = stations;
    for(auto station : stations){
        auxStations.erase(station.first);
        for(auto station2 : auxStations){
            if(station.first == station2.first)
                continue;
            temp = maxFlow(station.first, station2.first);
            if(temp > res){
                res = temp;
                st_temp.clear();
                st_temp[station.first]+=1;
                st_temp[station2.first]+=1;
            }
            else if(temp == res){
                if(st_temp.empty() || st_temp.find(station.first) == st_temp.end() || st_temp.find(station2.first) == st_temp.end()){
                    st_temp[station.first]+=1;
                    st_temp[station2.first]+=1;
                }
            }
        }
    }

    cout << "The stations that require the most amount of trains (" << res << " trains) are: " << endl;
    for(auto st : st_temp){
        cout << st.first << endl;

    }
}

