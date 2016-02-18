#include <iostream>
#include "std_lib_facilities.h"

using namespace std;

int main() {
    ifstream flights;
    ifstream airports;
    flights.open("/Users/BenDiliberto/ClionProjects/COA256 Coursework/flights.txt");
    airports.open("/Users/BenDiliberto/ClionProjects/COA256 Coursework/airports.txt");

    struct flightInformation {
        string starting;
        string ending;
        string airline;
        int price;
        int duration;

        flightInformation(string s, string e, string a, int p, int d)
                : starting(s), ending(e), airline(a), price(p), duration(d) {
        }
    };

    vector<vector<string> > flightInfo;
    vector<string> breakFlightInfo;
    string st;
    string en;
    string ai;
    string pr;
    string du;
    while (flights >> st >> en >> ai >> pr >> du) {
        breakFlightInfo.push_back(st);
        breakFlightInfo.push_back(en);
        breakFlightInfo.push_back(ai);
        breakFlightInfo.push_back(pr);
        breakFlightInfo.push_back(du);
        flightInfo.push_back(breakFlightInfo);
        breakFlightInfo.clear();
    }

    struct airportInformation {
        string code;
        string name;
        int dTax;
        int time;

        airportInformation(string c, string n, int d, int t)
                : code(c), name(n), dTax(d), time(t) {
        }
    };

    vector<vector<string> > airportInfo;
    vector<string> breakAirportInfo;
    string co;
    string na;
    string ta;
    string ti;
    while (airports >> co >> na >> ta >> ti) {
        breakAirportInfo.push_back(co);
        breakAirportInfo.push_back(na);
        breakAirportInfo.push_back(ta);
        breakAirportInfo.push_back(ti);
        airportInfo.push_back(breakAirportInfo);
        breakAirportInfo.clear();
    }

    cout << "Please enter the code of the airport you wish to fly from (Enter List if you wish to access information about a particular airport):" << "\n";
    string start;
    cin >> start;

    if(start=="List"){
        cout << "Please select an airport to display its information:" << "\n";
        for(int i=0;i<airportInfo.size();++i){
            cout << airportInfo[i][0] << endl;
        }
        cout << endl;
        string selAirport;
        cin >> selAirport;
        for(int i=0;i<airportInfo.size();++i){
            if(selAirport==airportInfo[i][0]){
                cout <<
                        "Code: " << airportInfo[i][0] <<
                        "   Name: " << airportInfo[i][1] << "\n" <<
                        "Departure Tax: " << airportInfo[i][2] <<
                        "   Connection Time: " << airportInfo[i][3] << "\n";
            }
        }
        cout << endl;
        cout << "These flights depart from this airport:" << "\n" << "\n";
        for(int i=0;i<flightInfo.size();++i){
            if(selAirport==flightInfo[i][0]){
                cout <<
                        "Destination: " << flightInfo[i][1] << "\n" <<
                        "    " << "Airline --> " << flightInfo[i][2] <<
                        "    " << "Total Time --> " << flightInfo[i][3] <<
                        "    " << "Total Cost --> " << flightInfo[i][4] << "\n";
            }
        }
        cout << endl;
        cout << "These flights are arriving at this airport:" << "\n" << "\n";
        for(int i=0;i<flightInfo.size();++i){
            if(selAirport==flightInfo[i][1]){
                cout <<
                        "Starting location: " << flightInfo[i][0] << "\n" <<
                        "    " << "Airline --> " << flightInfo[i][2] <<
                        "    " << "Total Time --> " << flightInfo[i][3] <<
                        "    " << "Total Cost --> " << flightInfo[i][4] << "\n";
            }
        }
    }

    cout << "\n" << "Please enter the code of your destination airport:" << "\n";
    string end;
    cin >> end;

    cout << "\n" << "Please enter the date you wish to depart on in the format DD/MM/YYYY" << "\n";
    string date;
    cin >> date;

    cout << "\n" << "These are the possible direct connections:" << "\n";
    for (int i = 0; i < flightInfo.size(); ++i) {
        if (start == flightInfo[i][0] && end == flightInfo[i][1]) {
            cout <<
                    "\n" << "Airline --> " << flightInfo[i][2] <<
                    "    " << "Total Time --> " << flightInfo[i][3] <<
                    "    " << "Total Cost --> " << flightInfo[i][4] << "\n";
        }
    }

    cout << "\n" << "\n" << "These are the possible flights with connections via other airports:" << "\n";
    for (int i = 0; i < flightInfo.size(); ++i) {
        int totalCost = 0;
        int totalTime = 0;
        if (start == flightInfo[i][0]) {
            string newStart = flightInfo[i][1];
            totalCost = totalCost + atoi(flightInfo[i][3].c_str());
            totalTime = totalTime + atoi(flightInfo[i][4].c_str());
            vector<vector<string>> completeFlights;
            vector<string> singleFlight;
            singleFlight.push_back(flightInfo[i][0]);
            singleFlight.push_back(flightInfo[i][1]);
            singleFlight.push_back(flightInfo[i][2]);
            completeFlights.push_back(singleFlight);
            singleFlight.clear();
            for (int j = 0; j < flightInfo.size(); ++j) {
                if (newStart == flightInfo[j][0]) {
                    if (end == flightInfo[j][1]) {
                        totalCost = totalCost + atoi(flightInfo[j][3].c_str());
                        totalTime = totalTime + atoi(flightInfo[j][4].c_str());
                        singleFlight.push_back(flightInfo[j][0]);
                        singleFlight.push_back(flightInfo[j][1]);
                        singleFlight.push_back(flightInfo[j][2]);
                        completeFlights.push_back(singleFlight);
                        singleFlight.clear();
                        cout <<
                                "\n" << "First Flight:   Starting Airport -->   " << completeFlights[0][0] <<
                                "   " << "Destination -->   " << completeFlights[0][1] <<
                                "   " << "Airline -->   " << completeFlights[0][2] <<
                                "\n" << "Second Flight:   Starting Airport -->   " << completeFlights[1][0] <<
                                "   " << "Destination -->   " << completeFlights[1][1] <<
                                "   " << "Airline -->   " << completeFlights[1][2] <<
                                "\n" << "Total Cost -->   " << totalCost <<
                                "   " << "Total Time -->   " << totalTime << "\n";
                    }
                    newStart = flightInfo[j][1];
                    totalCost = totalCost + atoi(flightInfo[j][3].c_str());
                    totalTime = totalTime + atoi(flightInfo[j][4].c_str());
                    singleFlight.push_back(flightInfo[j][0]);
                    singleFlight.push_back(flightInfo[j][1]);
                    singleFlight.push_back(flightInfo[j][2]);
                    completeFlights.push_back(singleFlight);
                    singleFlight.clear();
                    for (int k = 0; k < flightInfo.size(); ++k) {
                        if (newStart == flightInfo[k][0]) {
                            if (end == flightInfo[k][1]) {
                                totalCost = totalCost + atoi(flightInfo[k][3].c_str());
                                totalTime = totalTime + atoi(flightInfo[k][4].c_str());
                                singleFlight.push_back(flightInfo[k][0]);
                                singleFlight.push_back(flightInfo[k][1]);
                                singleFlight.push_back(flightInfo[k][2]);
                                completeFlights.push_back(singleFlight);
                                singleFlight.clear();
                                cout <<
                                        "\n" << "First Flight:   Starting Airport -->   " << completeFlights[0][0] <<
                                        "   " << "Destination -->   " << completeFlights[0][1] <<
                                        "   " << "Airline -->   " << completeFlights[0][2] <<
                                        "\n" << "Second Flight:   Starting Airport -->   " << completeFlights[1][0] <<
                                        "   " << "Destination -->   " << completeFlights[1][1] <<
                                        "   " << "Airline -->   " << completeFlights[1][2] <<
                                        "\n" << "Third Flight:   Starting Airport -->   " << completeFlights[2][0] <<
                                        "   " << "Destination -->   " << completeFlights[2][1] <<
                                        "   " << "Airline -->   " << completeFlights[2][2] <<
                                        "\n" << "Total Cost -->   " << totalCost <<
                                        "   " << "Total Time -->   " << totalTime << "\n";
                            }
                        }
                    }
                }
            }
        }
    }

}
