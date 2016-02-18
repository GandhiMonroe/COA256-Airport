#include "std_lib_facilities.h"

class searchAll {
public:
    vector<vector<string>> searchSingleConnections(string, string, vector<vector<string>>, int);

    vector<vector<string>> searchDoubleConnections(string, string, vector<vector<string>>, int);

    vector<vector<string>> searchDirect(vector<vector<string>>, string, string);

    int searchTax(vector<vector<string>>, string);

    int searchConnectTime(vector<vector<string>>, string);

    int searchCost(string, string, vector<vector<string>>, string);

    int searchTime(string, string, vector<vector<string>>, string);

    vector<string> splitDate(string);

private:
    string changeMonth(string);
};

vector<vector<string>> searchAll::searchSingleConnections(string start, string end, vector<vector<string>> flightInfo, int i) {
    vector<vector<string>> completeFlights;
    vector<string> singleFlight;
    string newStart;
    if (start == flightInfo[i][0]) {
        newStart = flightInfo[i][1];
        for (int j = 0; j < flightInfo.size(); ++j) {
            if (newStart == flightInfo[j][0]) {
                if (end == flightInfo[j][1]) {
                    singleFlight.push_back(flightInfo[i][0]);
                    singleFlight.push_back(flightInfo[i][1]);
                    singleFlight.push_back(flightInfo[i][2]);
                    completeFlights.push_back(singleFlight);
                    singleFlight.clear();
                    singleFlight.push_back(flightInfo[j][0]);
                    singleFlight.push_back(flightInfo[j][1]);
                    singleFlight.push_back(flightInfo[j][2]);
                    completeFlights.push_back(singleFlight);
                    singleFlight.clear();
                    return completeFlights;
                }
            }
        }
    }
}

vector<vector<string>> searchAll::searchDoubleConnections(string start, string end, vector<vector<string>> flightInfo, int i) {
    vector<vector<string>> completeFlights;
    vector<string> singleFlight;
    string newStart;
    if (start == flightInfo[i][0]) {
        newStart = flightInfo[i][1];
        for (int j = 0; j < flightInfo.size(); ++j) {
            if (newStart == flightInfo[j][0]) {
                newStart = flightInfo[j][1];
                for (int k = 0; k < flightInfo.size(); ++k) {
                    if (newStart == flightInfo[k][0]) {
                        if (end == flightInfo[k][1]) {
                            singleFlight.push_back(flightInfo[i][0]);
                            singleFlight.push_back(flightInfo[i][1]);
                            singleFlight.push_back(flightInfo[i][2]);
                            completeFlights.push_back(singleFlight);
                            singleFlight.clear();
                            singleFlight.push_back(flightInfo[j][0]);
                            singleFlight.push_back(flightInfo[j][1]);
                            singleFlight.push_back(flightInfo[j][2]);
                            completeFlights.push_back(singleFlight);
                            singleFlight.clear();
                            singleFlight.push_back(flightInfo[k][0]);
                            singleFlight.push_back(flightInfo[k][1]);
                            singleFlight.push_back(flightInfo[k][2]);
                            completeFlights.push_back(singleFlight);
                            singleFlight.clear();
                            return completeFlights;
                        }
                    }
                }
            }
        }
    }
}

int searchAll::searchCost(String start, String end, Vector<Vector<String>> flightInfo, String airline) {
    int totalCost = 0;
    for (int i = 0; i < flightInfo.size(); ++i) {
        if (start == flightInfo[i][0]) {
            if (end == flightInfo[i][1]) {
                if (airline == flightInfo[i][2]) {
                    totalCost = atoi(flightInfo[i][3].c_str());
                    return totalCost;
                }
            }
        }
    }
}

int searchAll::searchTime(String start, String end, Vector<Vector<String>> flightInfo, string airline) {
    int totalTime = 0;
    for (int i = 0; i < flightInfo.size(); ++i) {
        if (start == flightInfo[i][0]) {
            if (end == flightInfo[i][1]) {
                if (airline == flightInfo[i][2]) {
                    totalTime = atoi(flightInfo[i][4].c_str());
                    return totalTime;
                }
            }
        }
    }
}

vector<vector<string>> searchAll::searchDirect(Vector<Vector<String>> flightInfo, String start, String end) {
    vector<vector<string>> directFlights;
    vector<string> singleFlight;
    for (int i = 0; i < flightInfo.size(); ++i) {
        if (start == flightInfo[i][0] && end == flightInfo[i][1]) {
            singleFlight.push_back(flightInfo[i][2]);
            singleFlight.push_back(flightInfo[i][3]);
            singleFlight.push_back(flightInfo[i][4]);
            directFlights.push_back(singleFlight);
            singleFlight.clear();
        }
    }
    return directFlights;
}

int searchAll::searchTax(Vector<Vector<String>> airportInfo, String airportCode) {
    for (int i = 0; i < airportInfo.size(); ++i) {
        if (airportCode == airportInfo[i][0]) {
            return atoi(airportInfo[i][2].c_str());
        }
    }
}

int searchAll::searchConnectTime(Vector<Vector<String>> airportInfo, String airportCode) {
    for (int i = 0; i < airportInfo.size(); ++i) {
        if (airportCode == airportInfo[i][0]) {
            return atoi(airportInfo[i][3].c_str());
        }
    }
}

vector<string> searchAll::splitDate(String date) {
    vector<string> splitDate;
    if (date.length() == 10) {
        splitDate.push_back(date.substr(0, 2));
        splitDate.push_back(date.substr(3, 2));
        splitDate.push_back(date.substr(6, 4));
        if (atoi(splitDate[1].c_str()) >= 13) {
            error("Invalid Date");
        }
        splitDate[1] = searchAll::changeMonth(splitDate[1]);
        if (atoi(splitDate[0].c_str()) >= 31) {
            error("Invalid Date");
        }
        if (atoi(splitDate[2].c_str()) <= 2014) {
            error("Invalid Date");
        }
        return splitDate;
    }
    else {
        error("Invalid Date");
    }
}

string searchAll::changeMonth(string month) {
    if (month == "01") {
        month = "January";
    }
    else if (month == "02") {
        month = "February";
    }
    else if (month == "03") {
        month = "March";
    }
    else if (month == "04") {
        month = "April";
    }
    else if (month == "05") {
        month = "May";
    }
    else if (month == "06") {
        month = "June";
    }
    else if (month == "07") {
        month = "July";
    }
    else if (month == "08") {
        month = "August";
    }
    else if (month == "09") {
        month = "September";
    }
    else if (month == "10") {
        month = "October";
    }
    else if (month == "11") {
        month = "November";
    }
    else if (month == "12") {
        month = "December";
    }
    return month;
}