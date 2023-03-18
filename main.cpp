#include <iostream>
#include "src/Graph.h"

using namespace std;

Graph railway;

void showMenu() {
    cout << "\n";
    cout << "0) Exit\n";
    cout << "1) Show all stations\n";
    cout << "2) Show all connections\n";
    cout << "3) Show all connections from a station\n";
    cout << "4) Show all connections to a station\n";
    cout << "5) Show all connections between two stations\n";
    cout << "Choose an option: ";
}

int readOption() {
    int option;

    while (!(cin >> option)) {
        cin.clear();
        cin.ignore(1000000, '\n');
        cout << "Invalid option. Try again.\n";
    }
    return option;
}

int main() {
    railway.readFiles("../data/stations.csv", "../data/network.csv");
    //railway.printStations();
    for(auto &station : railway.getStations()) {
        station.second->printConnections();
    }
    return 0;
}
