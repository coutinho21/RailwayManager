#include <map>
#include "src/AuxMain.h"
#include <locale>

Graph railway;

int main() {
    setlocale(LC_ALL, "pt_PT.UTF-8");
    railway.readFiles("../data/stations.csv", "../data/network.csv");
    int option, option2;
    int k,total_flow, maximum_arrive;
    pair<int,int>min_cost_max_flow;
    string station,stationName, stationName2;
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
                cin.ignore(100000, '\n');
                stationName = readInput();
                cout << "To (Station name): ";
                stationName2 = readInput();
                railway.dijkstra(stationName, stationName2);
                break;
            case 3:
                cout << "\nFrom (Station Name): ";
                cin.ignore(100000, '\n');
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
                    cout << "Top k districts: ";
                    k = readOption();
                    railway.maxFlowDistrict(k);
                }
                else if(option2 == 2){
                    cout << "Top k municipalities: ";
                    k = readOption();
                    railway.maxFlowMunicipality(k);
                }
                else
                    cout << "\nInvalid option. Try again.\n";
                break;
            case 6:
                cout << "\nStation name: ";
                cin.ignore(100000, '\n');
                station = readInput();
                maximum_arrive = railway.maxTrainsArrival(station);
                if(maximum_arrive == 0){
                    break;
                }
                cout << maximum_arrive << " trains can arrive at " << station << " simultaneously.\n";
                break;
            case 7:
                cout << "\nFrom (Station Name): ";
                cin.ignore(100000, '\n');
                stationName = readInput();
                cout << "To (Station name): ";
                stationName2 = readInput();
                min_cost_max_flow = railway.minCostMaxFlow(stationName, stationName2);
                cout << "It is possible for " << min_cost_max_flow.first << " trains to travel simultaneously between " << stationName << " and " << stationName2 << " with a minimum cost of " << min_cost_max_flow.second << " euros.\n";
                break;
            default:
                cout << "\nInvalid option. Try again.\n";
        }
    } while (option != 0);
    return 0;
}