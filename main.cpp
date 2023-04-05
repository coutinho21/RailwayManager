#include "src/AuxMain.h"

Graph railway;

int main() {
    railway.readFiles("../data/stations.csv", "../data/network.csv");
    int option;
    int total_flow;
    string stationName, stationName2;

    do {
        showMenu();
        option = readOption();
        switch (option) {
            case 0:
                cout << "\nBye!\n";
                break;
            case 1:
                listStationAttributes(railway);
                break;
            case 2:
                cout << "\nFrom (Station Name): ";
                stationName = readInput();
                cout << "To (Station name): ";
                stationName2 = readInput();
                railway.dijkstra(stationName, stationName2);
                break;
            case 3:
                cout << "\nFrom (Station Name): ";
                stationName = readInput();
                cout << "To (Station name): ";
                stationName2 = readInput();
                total_flow = railway.maxFlow(stationName, stationName2);
                if(!total_flow)
                    cout << "It is not possible to travel between " << stationName << " and " << stationName2 << ".\n";
                else
                    cout << "It is possible for " << total_flow << " trains to travel simultaneously between " << stationName << " and " << stationName2 << ".\n";
                break;
            case 4:
                railway.MaxMaxFlow();
                break;
            default:
                cout << "\nInvalid option. Try again.\n";
        }
    } while (option != 0);
    return 0;
}