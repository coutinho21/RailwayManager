#include "src/AuxMain.h"

Graph railway;

int main() {
    railway.readFiles("../data/stations.csv", "../data/network.csv");
    int option, option2;
    int k,total_flow;
    string stationName, stationName2,district, municipality;
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
                railway.maxMaxFlow();
                break;
            case 5:
                cout << "\n0) Go back\n";
                cout << "1) District \n";
                cout << "2) Municipality \n";
                cout << "\nChoose an option: ";
                option2 = readOption();
                if(option2 == 1) {
                    cout << "\nDistrict name: ";
                    district = readInput();
                    railway.maxFlowDistrict(k, district);
                }
                else if(option2 == 2){
                    cout << "\nMunicipality name: ";
                    municipality = readInput();
                    railway.maxFlowMunicipality(k, municipality);
                }
                else
                    cout << "\nInvalid option. Try again.\n";
                break;
            default:
                cout << "\nInvalid option. Try again.\n";
        }
    } while (option != 0);
    return 0;
}