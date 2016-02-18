#include "std_lib_facilities.h"

class outputAll {
public:
    void outputList(vector<vector<string>>, vector<vector<string>>);

    int selectionChoice(vector<vector<string>>, string, string, vector<string>, int);

    vector<vector<vector<string>>> outputAllBookable(string, string, vector<vector<string>>, Vector<Vector<String>>, int, int);

    void outputDirect(vector<vector<string>>);

    void outputDoubleFlights(vector<vector<string>>, int);

    void outputSingleFlights(vector<vector<string>>, int);
private:
    void writeReceipt(string, vector<vector<string>>, string, string, vector<string>);

    void cancelBooking(string);
};

void outputAll::outputSingleFlights(Vector<Vector<String>> completeSingleFlights, int count) {
    cout <<
            "\n" << "Connection " << count << ":" <<
            "\n" << "First Flight:   Starting Airport -->   " << completeSingleFlights[0][0] <<
            "   " << "Destination -->   " << completeSingleFlights[0][1] <<
            "   " << "Airline -->   " << completeSingleFlights[0][2] <<
            "\n" << "Second Flight:   Starting Airport -->   " << completeSingleFlights[1][0] <<
            "   " << "Destination -->   " << completeSingleFlights[1][1] <<
            "   " << "Airline -->   " << completeSingleFlights[1][2] <<
            "\n" << "Total Cost -->   " << completeSingleFlights[2][0] <<
            "   " << "Total Time -->   " << completeSingleFlights[2][1] << "\n";
}

void outputAll::outputDoubleFlights(Vector<Vector<String>> completeFlights, int count) {
    cout <<
            "\n" << "Connection " << count << ":" <<
            "\n" << "First Flight:   Starting Airport -->   " << completeFlights[0][0] <<
            "   " << "Destination -->   " << completeFlights[0][1] <<
            "   " << "Airline -->   " << completeFlights[0][2] <<
            "\n" << "Second Flight:   Starting Airport -->   " << completeFlights[1][0] <<
            "   " << "Destination -->   " << completeFlights[1][1] <<
            "   " << "Airline -->   " << completeFlights[1][2] <<
            "\n" << "Third Flight:   Starting Airport -->   " << completeFlights[2][0] <<
            "   " << "Destination -->   " << completeFlights[2][1] <<
            "   " << "Airline -->   " << completeFlights[2][2] <<
            "\n" << "Total Cost -->   " << completeFlights[3][0] <<
            "   " << "Total Time -->   " << completeFlights[3][1] << "\n";
}

void outputAll::outputList(Vector<Vector<String>> flightInfo, Vector<Vector<String>> airportInfo) {
    cout << "Please select an airport to display its information:" << "\n";
    for (int i = 0; i < airportInfo.size(); ++i) {
        cout << airportInfo[i][0] << endl;
    }
    cout << endl;
    string selAirport;
    cin >> selAirport;
    for (int j = 0; j < airportInfo.size(); ++j) {
        if (selAirport == airportInfo[j][0]) {
            for (int i = 0; i < airportInfo.size(); ++i) {
                if (selAirport == airportInfo[i][0]) {
                    cout <<
                            "Code: " << airportInfo[i][0] <<
                            "   Name: " << airportInfo[i][1] << "\n" <<
                            "Departure Tax: " << airportInfo[i][2] <<
                            "   Connection Time: " << airportInfo[i][3] << "\n";
                }
            }
            cout << endl;
            cout << "These flights depart from this airport:" << "\n" << "\n";
            for (int i = 0; i < flightInfo.size(); ++i) {
                if (selAirport == flightInfo[i][0]) {
                    cout <<
                            "Destination: " << flightInfo[i][1] << "\n" <<
                            "    " << "Airline --> " << flightInfo[i][2] <<
                            "    " << "Total Time --> " << flightInfo[i][3] <<
                            "    " << "Total Cost --> " << flightInfo[i][4] << "\n";
                }
            }

            cout << endl;
            cout << "These flights are arriving at this airport:" << "\n" << "\n";
            for (int i = 0; i < flightInfo.size(); ++i) {
                if (selAirport == flightInfo[i][1]) {
                    cout <<
                            "Starting location: " << flightInfo[i][0] << "\n" <<
                            "    " << "Airline --> " << flightInfo[i][2] <<
                            "    " << "Total Time --> " << flightInfo[i][3] <<
                            "    " << "Total Cost --> " << flightInfo[i][4] << "\n";
                }
            }
        }
        else{
            error("Invalid Airport selection");
        }
    }
}

void outputAll::outputDirect(Vector<Vector<String>> directFlight) {
    for (int i = 0; i < directFlight.size(); ++i) {
        cout <<
                "Selection " << i + 1 <<
                "\n" << "Airline --> " << directFlight[i][0] <<
                "    " << "Total Time --> " << directFlight[i][1] <<
                "    " << "Total Cost --> " << directFlight[i][2] << "\n";
    }
}

void outputAll::cancelBooking(String selection) {
        cout << endl << "Are you sure you wish to cancel the booking process?";
        string enter;
        cin >> enter;
        if (selection == "Yes") {
            cout << endl << "Booking cancelled";
        }
};

void outputAll::writeReceipt(String selection, Vector<vector<string>> directFlight, String start, String end, Vector<string> splitDate) {
    ofstream receiptFile;
    receiptFile.open("/Users/BenDiliberto/ClionProjects/COA256-Airport/receipt.txt");
    int selection1 = atoi(selection.c_str()) - 1;
    receiptFile << "You have booked to go on a flight from:" << endl << start << " to " <<
            end << endl << "on: " << splitDate[0] << " " << splitDate[1] << " " << splitDate[2] << endl << endl << "It will cost: " << directFlight[selection1][1] <<
            " and will take: " << directFlight[selection1][2] << endl << "and you are flying with " <<
            directFlight[selection1][0] << endl;
    receiptFile.close();
}

int outputAll::selectionChoice(Vector<Vector<String>> directFlight, String start, String end, vector<string> splitDate, int complete) {
    outputDirect(directFlight);
    cout << "Please enter the number of the flight you wish to book, or enter 'Cancel' if you wish to exit the booking process" << endl;
    string selection;
    cin >> selection;
    if (selection == "Cancel") {
        cancelBooking(selection);
    }
    else if (selection == "Sort Cost") {

    }
    else if (selection == "Sort Time") {

    }
    else if (selection != "") {
        writeReceipt(selection, directFlight, start, end, splitDate);
        complete = 1;
        return complete;
    }
}