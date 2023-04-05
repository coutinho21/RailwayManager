#include "AuxMain.h"


void showMenu() {
    cout << "\n0) Exit\n";
    cout << "1) List station attributes\n";
    cout << "2) Shortest path between two stations\n";  //Dijkstra
    cout << "3) Maximum simultaneously travelling trains between two stations\n"; //2.1 Max Flow
    cout << "4) Pairs of stations that require most amount of trains\n"; //2.2 Max Max-flow between all pairs of stations
    cout << "5) Top-k municipalities or districts, regarding transportation needs\n";  //2.3 List of k districts or municipalities according to their max flow
    cout << "6) Maximum simultaneously arriving trains at a station\n"; //2.4
    cout << "\nChoose an option: ";
}

void showListStationAttributes() {
    cout << "\n0) Go back\n";
    cout << "1) Show all stations\n";
    cout << "2) Show all connections\n";
    cout << "3) Show all connections from a station\n";
    cout << "4) Show all connections to a station\n";
    cout << "\nChoose an option: ";
}

void listStationAttributes(Graph railway){
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
    cout << endl;
    return input;
}