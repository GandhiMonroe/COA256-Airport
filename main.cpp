#include <iostream>
#include "std_lib_facilities.h"
#include "output.cpp"
#include "search.cpp"

using namespace std;

int main() {
    int complete = 0;
    int errorvalue = 1;
    do {
        searchAll searchAll1;
        outputAll outputAll1;

        ifstream flights;
        ifstream airports;
        try {
            flights.open("/Users/BenDiliberto/ClionProjects/COA256-Airport/flights.txt");
            if (!flights) {
                error("Error opening file. Check filepath");
            }
            airports.open("/Users/BenDiliberto/ClionProjects/COA256-Airport/airports.txt");
            if (!airports) {
                error("Error opening file. Check filepath");
            }
        }
        catch (runtime_error &e) {
            cerr << "Runtime Error: " << e.what() << endl;
            return 0;
        }

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

        if (start == "List") {
            do {
                try {
                    outputAll1.outputList(flightInfo, airportInfo);
                }
                catch (runtime_error &e) {
                    cerr << "Runtime Error: " << e.what() << endl;
                    errorvalue = 1;
                }
            }while(errorvalue==1);
        }

        cout << "\n" << "Please enter the code of your destination airport:" << "\n";
        string end;
        cin >> end;

        vector<string> splitDate;

        do {
            try {
                cout << "\n" << "Please enter the date you wish to depart on in the format DD/MM/YYYY" << "\n";
                string date;
                cin >> date;
                errorvalue = 0;
                splitDate = searchAll1.splitDate(date);
            }
            catch (runtime_error &e) {
                cerr << "Runtime Error: " << e.what() << endl;
                errorvalue = 1;
            }
        } while (errorvalue == 1);

        vector<vector<vector<string>>> allBookable;
        vector<vector<string>> directFlight = searchAll1.searchDirect(flightInfo, start, end);
        int totalTime = 0;
        int totalCost = 0;
        if (directFlight.size() != 0) {
            cout << "\n" << "These are the possible direct connections:" << "\n";
            complete = outputAll1.selectionChoice(directFlight, start, end, splitDate, complete);
        }
        else {
            cout << "\n" << "There are no direct flights between these airports" << "\n";
            vector<vector<string>> completeSingleFlights;
            int count = 0;
            for (int i = 0; i < flightInfo.size(); ++i) {
                completeSingleFlights = searchAll1.searchSingleConnections(start, end, flightInfo, i);
                if (completeSingleFlights.size() != 0) {
                    for (int j = 0; j < completeSingleFlights.size(); ++j) {
                        totalCost += searchAll1.searchCost(completeSingleFlights[j][0], completeSingleFlights[j][1], flightInfo, completeSingleFlights[j][2]) + searchAll1.searchTax(airportInfo, completeSingleFlights[j][0]);
                        totalTime += searchAll1.searchTime(completeSingleFlights[j][0], completeSingleFlights[j][1], flightInfo, completeSingleFlights[j][2]) + searchAll1.searchConnectTime(airportInfo, completeSingleFlights[j][0]);
                    }
                    ++count;
                    vector<string> totals;
                    totals.push_back(to_string(totalCost));
                    totals.push_back(to_string(totalTime));
                    completeSingleFlights.push_back(totals);
                    outputAll1.outputSingleFlights(completeSingleFlights, count);
                    allBookable.push_back(completeSingleFlights);
                    completeSingleFlights.clear();
                    totalCost = 0;
                    totalTime = 0;
                }
            }
            vector<vector<string>> completeDoubleFlights;
            for (int i = 0; i < flightInfo.size(); ++i) {
                completeDoubleFlights = searchAll1.searchDoubleConnections(start, end, flightInfo, i);
                if (completeDoubleFlights.size() != 0) {
                    for (int j = 0; j < completeDoubleFlights.size(); ++j) {
                        totalCost += searchAll1.searchCost(completeDoubleFlights[j][0], completeDoubleFlights[j][1], flightInfo, completeDoubleFlights[j][2]) + searchAll1.searchTax(airportInfo, completeDoubleFlights[j][0]);
                        totalTime += searchAll1.searchTime(completeDoubleFlights[j][0], completeDoubleFlights[j][1], flightInfo, completeDoubleFlights[j][2]) + searchAll1.searchConnectTime(airportInfo, completeDoubleFlights[j][0]);
                    }
                    ++count;
                    vector<string> totals;
                    totals.push_back(to_string(totalCost));
                    totals.push_back(to_string(totalTime));
                    completeDoubleFlights.push_back(totals);
                    outputAll1.outputDoubleFlights(completeDoubleFlights, count);
                    allBookable.push_back(completeDoubleFlights);
                    completeDoubleFlights.clear();
                    totalCost = 0;
                    totalTime = 0;
                }
            }
            if(allBookable.size()>0){
                cout << endl << "Please enter the number of the selection you wish to book, enter 'Cancel' if you wish to exit the booking process, or enter 'Sort Time'/'Sort Cost' to sort the available flights by the selected data: " << endl;
                string selection;
                cin >> selection;
                if (selection == "Cancel") {
                    cout << endl << "Are you sure you wish to cancel the booking process?" << endl;
                    cin >> selection;
                    if (selection == "Yes") {
                        cout << "Booking cancelled";
                    }
                }
                if (atoi(selection.c_str()) > 0) {
                    ofstream receiptFile;
                    receiptFile.open("/Users/BenDiliberto/ClionProjects/COA256-Airport/receipt.txt");
                    int selection1 = atoi(selection.c_str()) - 1;
                    int noFlights = allBookable[selection1].size();
                    receiptFile << "You have booked the connection flight from: " << endl;
                    for (int i = 0; i < noFlights - 1; ++i) {
                        receiptFile << allBookable[selection1][i][0] << " to " << allBookable[selection1][i][1] << " with the airline " << allBookable[selection1][i][2] << endl;
                    }
                    receiptFile << "on: " << splitDate[0] << " " << splitDate[1] << " " << splitDate[2] << endl <<
                            "This will cost: " << allBookable[selection1][noFlights - 1][0] << "      and will take: " << allBookable[selection1][noFlights - 1][1] << endl;
                    receiptFile.close();
                    complete = 1;
                }
            }
            else{
                cout << endl << "There are no flights between these two locations" << endl << endl;
            }
        }
    }while(complete==0);
}
