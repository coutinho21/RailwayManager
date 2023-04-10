#include <map>
#include "Graph.h"
#include "Tripaux.h"

/**
 * @brief Constructor of the Graph class
 * @param file1
 * @param file2
 * This class reads the csv files with the data set and creates the graph
 */
void Graph::readFiles(const string &file1, const string &file2) {
    ifstream stationsFile, linesFile;
    string line;
    int counter = 1;

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
                    if (tempstr.back() == '\"') {
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
            counter++;
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

/**
 * @brief Adds a station to the graph
 * @param pStation
 */
void Graph::addStation(Station *pStation) {
    if (stations.find(pStation->getName()) == stations.end()) {
        stations[pStation->getName()] = pStation;
        size++;
    }
}

Station *Graph::getStation(const string &basicString) {
    return stations[basicString];
}

/**
 * @brief Adds an edge to the graph
 * @param source
 * @param destination
 * @param capacity
 * @param service
 */
void Graph::addEdge(Station *source, Station *destination, int capacity, const string &service) {
    source->addTrip(destination, capacity, service);
    destination->addTrip(source, capacity, service);
}

/**
 * @brief Removes an edge from the graph
 * @param source
 * @param destination
 */
void Graph::removeEdge(Station *source, Station *destination) {
    source->removeTrip(destination);
    destination->removeTrip(source);
}

/**
 * @brief Adds a line to the graph
 * @param basicString
 * @param pStation
 */
void Graph::addLine(const string &basicString, Station *pStation) {
    lines[basicString].push_back(pStation);
}

unordered_map<string, Station *> &Graph::getStations() {
    return stations;
}

void Graph::setStations(const unordered_map<string, Station *> &stations) {
    Graph::stations = stations;
}

unordered_map<string, vector<Station *>> &Graph::getLines() {
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

/**
 * @brief Prints all the stations in the graph
 */
void Graph::printStations() {
    cout << "\nAll stations:" << endl;
    for (auto &station: this->stations)
        cout << "\tStation name -> " << station.second->getName() << endl
             << "\tStation district -> " << station.second->getDistrict() << endl
             << "\tStation municipality -> " << station.second->getMunicipality() << endl
             << "\tStation township -> " << station.second->getTownship() << endl
             << "\tStation line -> " << station.second->getLine() << endl << "\n\n";
}

/**
 * @brief Prints all the connections in from all stations of the graph
 */
void Graph::printAllConnections() {
    cout << "\nAll connections:" << endl;
    for (auto &station: this->stations)
        station.second->printConnections();
}

/**
 * @brief Prints all the connections in from a specific station
 * @param stationName
 */
void Graph::printConnectionsTo(const string &stationName) {
    cout << "\nConnections to " << stationName << ':' << endl;
    for (auto &station: this->stations)
        for (auto &connection: station.second->getTrips())
            if (connection->getDestination()->getName() == stationName)
                cout << '\t' << station.second->getName() << " -> " << connection->getDestination()->getName() << endl;

}

/**
 * @brief Dijkstra's algorithm
 * @param stationName
 * @param destination
 * This function is used to find the shortest path between two stations using the Dijkstra's algorithm
 * Time Complexity: O(|V| + |E|), where |V| is the number of vertices and |E| is the number of edges
 */
void Graph::dijkstra(const string &source, const string &destination) {
    unordered_map<string, Station *> visited;
    unordered_map<string, Station *> unvisited;
    unordered_map<string, Station *> previous;
    unordered_map<string, int> distance;
    int sf = 1;
    int df = 1;


    for (auto &station: stations) {
        distance[station.first] = INT_MAX;
        unvisited[station.first] = station.second;

        if (station.first == source) sf = 0;
        if (station.first == destination) df = 0;
    }

    if (sf) {
        cout << "Invalid Source Station Name.\n";
        return;
    }
    if (df) {
        cout << "Invalid Destination Station Name.\n";
        return;
    }

    distance[source] = 0;

    while (!unvisited.empty()) {
        Station *current = unvisited.begin()->second;
        for (auto &station: unvisited) {
            if (distance[station.first] < distance[current->getName()])
                current = station.second;
        }

        if (current->getName() == destination)
            break;


        unvisited.erase(current->getName());
        visited[current->getName()] = current;

        for (auto &connection: current->getTrips()) {
            if (visited.find(connection->getDestination()->getName()) == visited.end()) {
                int alt = distance[current->getName()] + 1;
                if (alt < distance[connection->getDestination()->getName()]) {
                    distance[connection->getDestination()->getName()] = alt;
                    previous[connection->getDestination()->getName()] = current;
                }
            }
        }
    }

    vector<string> path;
    Station *current = stations[destination];
    while (current != nullptr) {
        path.push_back(current->getName());
        current = previous[current->getName()];
    }

    if (path[path.size() - 1] != source) {
        cout << "\nThere is no path from " << source << " to " << destination << endl;
        return;
    }

    cout << "\nShortest path from " << source << " to " << destination << " is:" << endl << "\n";
    for (int i = path.size() - 1; i >= 0; i--)
        cout << path[i] << (i == 0 ? "" : " -> ");
    cout << endl;
}

/**
 * @brief Finds a station in the graph
 * @param source
 * @return the station if found, nullptr otherwise
 */
Station *Graph::findStation(const string &source) {
    for (const auto &station: stations)
        if (station.first == source)
            return station.second;
    return nullptr;
}

/**
 * @brief BFS using Edmonds-Karp algorithm
 * @param source
 * @param destination
 * @return the station if found, nullptr otherwise
 * This function is used in the maxFlow function using the Edmonds-Karp algorithm
 * Time Complexity: O(|V| * |E|^2) where |V| is the number of vertices and |E| is the number of edges
 */
bool Graph::bfskarp(const string &source, const string &destination) {
    std::queue<Station *> q;
    for (auto station: stations) {
        station.second->setVisited(false);
        station.second->setPath(nullptr);
        for (auto e: station.second->getTrips()) {
            delete e->getReverse();
            e->setReverse(nullptr);
        }
    }
    q.push(findStation(source));
    q.front()->setVisited(true);
    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        for (auto e: v->getTrips()) {
            auto w = e->getDestination();
            if (!w->isVisited() && e->getCapacity() - e->getFlow() > 0) {
                w->setPath(e);
                w->setVisited(true);
                q.push(w);
                if (w->getName() == destination) return true;
            }
        }
        for (auto e: v->getIncoming()) {
            auto w = e->getSource();
            if (!w->isVisited() && e->getFlow() != 0) {
                Trip *er = new Trip(e->getDestination(), e->getSource(), e->getFlow(), e->getService());
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

/**
 * @brief Max Flow using Edmonds-Karp algorithm
 * @param source
 * @param destination
 * @return the maximum flow (capacity) between two stations
 * This function is uses the Edmonds-Karp algorithm to find the maximum flow between two stations
 * Time Complexity: O(|V| * |E|^2) where |V| is the number of vertices and |E| is the number of edges
 */
int Graph::maxFlow(const string &source, const string &destination) {
    int sf = 1;
    int df = 1;

    for (const auto &station: stations) {
        for (auto trip: station.second->getTrips())
            trip->setFlow(0);

        if (station.first == source) sf = 0;
        if (station.first == destination) df = 0;
    }

    if (sf) {
        cout << "Invalid Source Station Name.\n";
        cout << source << endl;
        return 0;
    }
    if (df) {
        cout << "Invalid Destination Station Name.\n";
        return 0;
    }

    int total_flow = 0;
    while (bfskarp(source, destination)) {
        int mrc = INT32_MAX;
        auto e = findStation(destination)->getPath();
        while (true) {
            if (e->getReverse() == nullptr && e->getCapacity() - e->getFlow() < mrc)
                mrc = e->getCapacity() - e->getFlow();
            if (e->getReverse() != nullptr && e->getReverse()->getFlow() < mrc) mrc = e->getReverse()->getFlow();
            if (e->getSource()->getName() == source) break;
            e = e->getSource()->getPath();
        }
        e = findStation(destination)->getPath();
        while (true) {
            if (e->getReverse() != nullptr)
                e->getReverse()->setFlow(e->getReverse()->getFlow() - mrc);
            else
                e->setFlow(e->getFlow() + mrc);

            if (e->getSource()->getName() == source) break;
            e = e->getSource()->getPath();
        }
        total_flow += mrc;
    }
    return total_flow;
}

/**
 * @brief Does the maxFlow function for all the stations
 * In the end, prints the stations that require the most amount of trains
 * Complexity: O( |V|^2 * (|V| * |E|^2)) where |V| is the number of vertices and |E| is the number of edges
 */
void Graph::maxMaxFlow() {
    int res = 0;
    int temp;
    vector<pair<string, string>> allMaxFlow;
    unordered_map<string, int> st_temp;
    unordered_map<string, Station *> auxStations = stations;
    for (const auto &station: stations) {
        auxStations.erase(station.first);
        for (const auto &station2: auxStations) {
            if (station.first == station2.first)
                continue;
            temp = maxFlow(station.first, station2.first);

            if (temp > res) {
                res = temp;
                st_temp.clear();
                st_temp[station.first] += 1;
                st_temp[station2.first] += 1;
            } else if (temp == res) {
                if (st_temp.empty() || st_temp.find(station.first) == st_temp.end() ||
                    st_temp.find(station2.first) == st_temp.end()) {
                    st_temp[station.first] += 1;
                    st_temp[station2.first] += 1;
                }
            }
        }
    }

    cout << "The stations that require the most amount of trains (" << res << " trains) are: " << endl;
    for (const auto &st: st_temp) {
        cout << "- " << st.first << endl;

    }
}

/**
 * @brief Does the maxFlow function for every district
 * @param k where k is the number of districts
 * In the end, prints the the k districts that require the most amount of trains
 * Complexity: O(|V| * |E|^2) where |V| is the number of vertices and |E| is the number of edges
 */
void Graph::maxFlowDistrict(int k) {
    int ktemp = k;
    unordered_map<string, int> d_temp;
    unordered_map<string, Station *> auxStations = stations;
    for (const auto &station: stations) {
        auxStations.erase(station.first);
        for (const auto &station2: auxStations) {
            if (station.first == station2.first)
                continue;
            if (station.second->getDistrict() != station2.second->getDistrict()) {
                continue;
            }
            d_temp[station.second->getDistrict()] += maxFlow(station.first, station2.first);
        }
    }
    while (k > 0) {
        int max = 0;
        string maxD;
        for (const auto &d: d_temp) {
            if (d.second > max) {
                max = d.second;
                maxD = d.first;
            }
        }
        cout << ktemp - k + 1 << "º " << maxD << " ideally requires " << max << " trains." << endl;
        d_temp.erase(maxD);
        k--;
    }
}

/**
 * @brief Does the maxFlow function for every municipality
 * @param k where k is the number of municipalities
 * In the end, prints the the k municipalities that require the most amount of trains
 * Complexity: O(|V| * |E|^2) where |V| is the number of vertices and |E| is the number of edges
 */
void Graph::maxFlowMunicipality(int k) {
    int ktemp = k;
    unordered_map<string, int> d_temp;
    unordered_map<string, Station *> auxStations = stations;
    for (const auto &station: stations) {
        auxStations.erase(station.first);
        for (const auto &station2: auxStations) {
            if (station.first == station2.first)
                continue;
            if (station.second->getMunicipality() != station2.second->getMunicipality()) {
                continue;
            }
            d_temp[station.second->getMunicipality()] += maxFlow(station.first, station2.first);
        }
    }
    while (k > 0) {
        int max = 0;
        string maxD;
        for (const auto &d: d_temp) {
            if (d.second > max) {
                max = d.second;
                maxD = d.first;
            }
        }
        cout << ktemp - k + 1 << "º " << maxD << " ideally requires " << max << " trains." << endl;
        d_temp.erase(maxD);
        k--;
    }
}

/**
 * @brief Calculates the maximum number of trains that can arrive at a station
 * @param station
 * @return the maximum number of trains that can arrive at a given station
 * Complexity: O(|V| * |E|^2) where |V| is the number of vertices and |E| is the number of edges
 */
int Graph::maxTrainsArrival(const string &station) {
    int sf = 0;
    string super_source = "super_source";
    auto *super_source_station = new Station(super_source, "sp", "sp","sp","sp");

    stations[super_source] = super_source_station;
    for (auto &s: stations) {
        if (s.first != station && stations[s.first]->getTrips().size() == 1) {
            addEdge(s.second,super_source_station, INT_MAX, "SP");
        }
        if (s.first == station) {
            sf = 1;
        }
    }

    if(sf == 0) {
        cout << "Invalid Station Name." << endl;
        return 0;
    }


    // find maximum flow from super source to super sink
    int max_flow = maxFlow(super_source, station);

    // find the flow arriving at the given station
    int station_flow = 0;
    for (auto &neighbor: stations[station]->getTrips()) {
        if (neighbor->getDestination()->getName() != station) {
            station_flow += neighbor->getCapacity();
        }
    }


    for(auto &s: stations) {
        removeEdge(super_source_station,s.second);
    }

    // return the maximum number of trains that can simultaneously arrive at the given station
    return min(station_flow, max_flow);
}

/**
 * @brief Calculates the maximum number of trains that can travel between two stations with minimum cost for the company
 * @param source
 * @param destination
 * @return a pair with the maximum trains and the minimum cost
 * Uses BFS algorithm
 * Complexity: O(|V| + |E|) where |V| is the number of vertices and |E| is the number of edges
 */
pair<int,int> Graph::minCostMaxFlow(const string& source, const string& destination) {
    int n = stations.size();
    unordered_map<string, int> stationIndex(n);
    vector<vector<Tripaux>> graph(n);
    int index = 0;
    for (auto& it : stations) {
        stationIndex[it.first] = index++;
        Station* station = it.second;
        for (Trip* trip : station->getTrips()) {
            int sourceIndex = stationIndex[trip->getSource()->getName()];
            int destIndex = stationIndex[trip->getDestination()->getName()];
            graph[sourceIndex].emplace_back(trip->getSource(), trip->getDestination(), trip->getCapacity(), (trip->getService() == "STANDARD" ? 2 : 4), (int)graph[destIndex].size());
            graph[destIndex].emplace_back(trip->getDestination(), trip->getSource(), 0, -(trip->getService() == "STANDARD" ? 2 : 4), (int)graph[sourceIndex].size() - 1);
        }
    }
    int sourceIndex = stationIndex[source];
    int sinkIndex = stationIndex[destination];
    int maxFlow = 0;
    int minCost = 0;

    while (true) {
        vector<int> dist(n, INT_MAX);
        vector<int> parent(n, -1);
        vector<int> parentEdge(n, -1);
        vector<bool> inQueue(n, false);

        dist[sourceIndex] = 0;
        queue<int> q;
        q.push(sourceIndex);
        inQueue[sourceIndex] = true;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            inQueue[u] = false;

            for (int i = 0; i < graph[u].size(); i++) {
                Tripaux& e = graph[u][i];
                int v = stationIndex[e.getDestination()->getName()];
                int w = e.getCost();

                if (e.capacity == 0) continue;

                int newDist = dist[u] + w;
                if (newDist < dist[v]) {
                    dist[v] = newDist;
                    parent[v] = u;
                    parentEdge[v] = i;

                    if (!inQueue[v]) {
                        q.push(v);
                        inQueue[v] = true;
                    }
                }
            }
        }

        if (parent[sinkIndex] == -1) break;

        int u = sinkIndex;
        int flow = INT_MAX;

        while (u != sourceIndex) {
            int v = parent[u];
            int i = parentEdge[u];
            flow = min(flow, graph[v][i].capacity);
            u = v;
        }

        u = sinkIndex;

        while (u != sourceIndex) {
            int v = parent[u];
            int i = parentEdge[u];
            graph[v][i].capacity -= flow;
            int revIndex = graph[v][i].getRev();
            if (revIndex >= 0 && revIndex < graph[u].size()) {
                graph[u][revIndex].capacity += flow;
            }
            minCost += flow * graph[v][i].getCost();
            u = v;
        }

        maxFlow += flow;
    }
    return {maxFlow, minCost};
}