#include <iostream>
#include "src/Graph.h"

using namespace std;

Graph railway;

void showMenu() {
    cout << "\n0) Exit\n";
    cout << "1) List station attributes\n";
    cout << "2) Shortest path between two stations\n";
    cout << "Choose an option: ";
}

void showListStationAttributes(){
    cout << "\n0) Go back\n";
    cout << "1) Show all stations\n";
    cout << "2) Show all connections\n";
    cout << "3) Show all connections from a station\n";
    cout << "4) Show all connections to a station\n";
    cout << "Choose an option: ";
}

int readOption() {
    int option;

    if(!(cin >> option)) {
        cin.clear();
        cin.ignore(1000, '\n');
        return 100;
    }
    return option;
}

string readInput(){
    string input;
    getline(cin >> ws, input);
    cout << std::endl;
    return input;
}

void listStationAttributes(){
    int option;
    string stationName, stationName2;
    do {
        showListStationAttributes();
        option = readOption();
        switch (option) {
            case 0:
                break;
            case 1:
                railway.printStations();
                break;
            case 2:
                railway.printAllConnections();
                break;
            case 3:
                cout << "\nStation name: ";
                stationName = readInput();
                railway.getStations()[stationName]->printConnections();
                break;
            case 4:
                cout << "\nStation name: ";
                stationName = readInput();
                railway.printConnectionsTo(stationName);
                break;
            default:
                cout << "\nInvalid option. Try again.\n";
        }
    } while (option != 0);
}

int main() {
    railway.readFiles("../data/stations.csv", "../data/network.csv");
    int option;
    string stationName, stationName2;
    do {
        showMenu();
        option = readOption();
        switch (option) {
            case 0:
                cout << "\nBye!\n";
                break;
            case 1:
                listStationAttributes();
                break;
            case 2:
                cout << "\nStation name: ";
                stationName = readInput();
                cout << "Station name: ";
                stationName2 = readInput();
                railway.dijkstra(stationName, stationName2);
                break;
            default:
                cout << "\nInvalid option. Try again.\n";
        }
    } while (option != 0);
    return 0;
}
