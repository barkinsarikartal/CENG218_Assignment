#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "Passenger.h"

using namespace std;

class Flight{
public:
    string flightNumber, destination;
    int passengerCounter = 0, maxSeats = 40;
    vector<Passenger> passengerVector;
public:
    Flight(string userFlightNumber, string userDestination)
    : flightNumber(userFlightNumber), destination(userDestination) {}
    Flight()= default;
public:
    bool reserveSeat(Passenger passenger){
        if(this->passengerCounter < this->maxSeats){
            passengerVector.push_back(passenger);
            passengerCounter++;
            return true;
        }
        else{
            return false;
        }
    }
    void checkReservation(string userName, string userSurname){
        auto checkedPersonSurname = std::find_if(passengerVector.begin(), passengerVector.end(), [userSurname](const Passenger& passenger) {
            return passenger.surname == userSurname;
        });

        if (checkedPersonSurname != passengerVector.end()) {
            auto checkedPersonName = std::find_if(passengerVector.begin(), passengerVector.end(), [userName](const Passenger& passenger) {
                return passenger.name == userName;
            });
            if(checkedPersonName != passengerVector.end() && checkedPersonName == checkedPersonSurname){
                cout << "Your Flight Number is: " << this->flightNumber << endl;
            }
            else{
                cout << "There is No Passengers With This Name." << endl;
            }
        }
        else {
            cout << "There is No Passengers With This Name." << endl;
        }
    }
    bool cancelReservation(string userName, string userSurname) {

        auto deletedPersonSurname = std::find_if(passengerVector.begin(), passengerVector.end(), [userSurname](const Passenger& passenger) {
            return passenger.surname == userSurname;
        });

        if (deletedPersonSurname != passengerVector.end()) {
            auto deletedPersonName = std::find_if(passengerVector.begin(), passengerVector.end(), [userName](const Passenger& passenger) {
                return passenger.name == userName;
            });
            if(deletedPersonName != passengerVector.end() && deletedPersonName == deletedPersonSurname){
                passengerVector.erase(deletedPersonName);
                cout << "Reservation Cancelled Successfully." << endl;
                passengerCounter--;
                return true;
            }
            else{
                cout << "Couldn't Cancel The Reservation." << endl;
                return false;
            }
        }
        else {
            cout << "Couldn't Cancel The Reservation." << endl;
            return false;
        }
    }
    [[nodiscard]] unsigned int numberOfPassengers() const {
        return passengerVector.size();
    }
    void printPassengers() {
        int i = 1;
        for (auto& passenger : passengerVector) {
            cout << i << ". ";
            passenger.display();
            i++;
        }
        cout << to_string(numberOfPassengers()) + " Passengers Aboard" << endl;
    }
    bool searchForSurname(string userSurname){ //change this to sortBySurname.
        auto result = std::find_if(passengerVector.begin(), passengerVector.end(),
                                   [&userSurname](const Passenger& p) {
                                       return p.surname == userSurname;
                                   });
        if (result != passengerVector.end()) {
            return true;
        } else {
            return false;
        }
    }
    void display() const{
        cout << "Flight No: " << this->flightNumber << ", Going to: " << this->destination << ", Passengers Aboard: " << this->passengerCounter << endl;
    }
    bool isFlyingTo(const string& userDestination){
        if(userDestination == this->destination){
            return true;
        }
        else{
            return false;
        }
    }
};

class FlightManager{
public:
    int flightCounter = 0;
    vector<Flight> flightVector;
public:
    bool addFlight(const Flight& flight){
        if(flight.passengerCounter < flight.maxSeats){
            flightVector.push_back(flight);
            flightCounter++;
            return true;
        }
        else{
            return false;
        }
    }
    bool removeFlight(const string& flightNumber){
        auto deletedFlight = std::find_if(flightVector.begin(), flightVector.end(),
                                   [&flightNumber](const Flight& flight) {
                                       return flight.flightNumber == flightNumber;
                                   });
        if (deletedFlight != flightVector.end()) {
            flightVector.erase(deletedFlight);
            flightCounter--;
            return true;
        } else {
            return false;
        }
    }
    void listAllFlights(){
        int i = 1;
        for (auto& flight : flightVector) {
            cout << i << ". ";
            flight.display();
            i++;
        }
        cout << to_string(i-1) + " Flights Ahead" << endl;
    }

    Flight getFlightByNumber(const string& flightNumber){
        if (isThereAFlight(flightNumber)) {
            auto findFlight = find_if(flightVector.begin(), flightVector.end(),
                                           [&flightNumber](const Flight& flight) {
                                               return flight.flightNumber == flightNumber;
                                           });

            if (findFlight != flightVector.end()) {
                int index = distance(flightVector.begin(), findFlight);
                return flightVector[index];
            }
        }
        else {
            cout << "There is No Flights With This Number." << endl;
        }
    }

    bool isThereAFlight(const string& flightNumber){
        auto findFlight = std::find_if(flightVector.begin(), flightVector.end(),
                                       [&flightNumber](const Flight& flight) {
                                           return flight.flightNumber == flightNumber;
                                       });
        if (findFlight != flightVector.end()) {
            return true;
        } else {
            return false;
        }
    }
};

void mainPassengerMenu();
void flightManagerMenu();

int main() {

    string userName, userSurname, userFlightNumber, userDestination;
    char userGender;
    int passengerMenuChoice = 0, flightMenuChoice = 0;

    FlightManager flightManager = *new FlightManager;

    do{
        flightManagerMenu();
        cin >> flightMenuChoice;
        if(flightMenuChoice == 1){
            cout << "Enter Flight Number:" << endl;
            cin >> userFlightNumber;
            cout << "Enter Destination:" << endl;
            cin >> userDestination;
            Flight flight = *new Flight(userFlightNumber, userDestination);
            if(flightManager.addFlight(flight)){
                cout << "Flight Added to The System Successfully." << endl;
            }
            else{
                cout << "Flight Could Not Be Added to The System." << endl;
            }
            userFlightNumber = {}, userDestination = {};
        }
        else if(flightMenuChoice == 2){
            cout << "Enter Flight Number:" << endl;
            cin >> userFlightNumber;
            if(flightManager.removeFlight(userFlightNumber)){
                cout << "Flight Removed from The System Successfully." << endl;
            }
            else{
                cout << "Flight Could Not Be Removed from The System." << endl;
                userFlightNumber = {};
            }
        }
        else if(flightMenuChoice == 3){
            flightManager.listAllFlights();
        }

        else if(flightMenuChoice == 4){ //fix this and you are good to go.
            mainPassengerMenu();
            cin >> passengerMenuChoice;
            while(true){
                if(passengerMenuChoice == 1){
                    cout << "Enter Passenger's First Name:" << endl;
                    cin >> userName;
                    cout << "Enter Passenger's Last Name:" << endl;
                    cin >> userSurname;
                    cout << "Enter Passenger's Gender (M/F):" << endl;
                    cin >> userGender;
                    cout << "Enter the Flight Number You Want to Reserve a Ticket From:" << endl;
                    cin >> userFlightNumber;

                    Passenger passenger = *new Passenger(userName, userSurname, userGender);

                    if(flightManager.isThereAFlight(userFlightNumber)){
                        flightManager.getFlightByNumber(userFlightNumber).reserveSeat(passenger);
                        cout << "Reservation Done Successfully." << endl;
                    }
                    else{
                        cout << "Reservation Could Not Be Done." << endl;
                    }
                    userName = {}, userSurname = {}, userGender = {}, userFlightNumber = {};
                }
                else if(passengerMenuChoice == 2){
                    cout << "Enter the First Name of the Passenger Whose Reservation You Want to Cancel:\n";
                    cin >> userName;
                    cout << "Enter the Last Name of the Passenger Whose Reservation You Want to Cancel:\n";
                    cin >> userSurname;
                    cout << "Enter the Flight Number You Want to Cancel the Ticket From:" << endl;
                    cin >> userFlightNumber;

                    if(flightManager.isThereAFlight(userFlightNumber)){
                        flightManager.getFlightByNumber(userFlightNumber).cancelReservation(userName, userSurname);
                    }

                    userName = {}, userSurname = {}, userFlightNumber = {};
                    passengerMenuChoice = {};
                }
                else if(passengerMenuChoice == 3){
                    cout << "Enter Your First Name:\n";
                    cin >> userName;
                    cout << "Enter Your Last Name:\n";
                    cin >> userSurname;
                    cout << "Enter Your Flight Number:" << endl;
                    cin >> userFlightNumber;

                    flightManager.getFlightByNumber(userFlightNumber).checkReservation(userName, userSurname);
                    userName = {}, userSurname = {}, userFlightNumber = {};
                    passengerMenuChoice = {};
                }
                else if(passengerMenuChoice == 4){
                    cout << "Enter the Number of Flight You Want to Display Passengers of:" << endl;
                    cin >> userFlightNumber;

                    cout << "Passenger List:\n";
                    flightManager.getFlightByNumber(userFlightNumber).printPassengers();
                    passengerMenuChoice = {};
                }
                else if(passengerMenuChoice == 5){
                    passengerMenuChoice = {};
                    break;
                }

                else{
                    cout << "Invalid choice.\n"; //fix the char bug!
                }

            }
        }

        else if(flightMenuChoice == 5){
            cout << "Exiting Program.\n";
        }
        else{
            cout << "Invalid choice.\n"; //fix the char bug!
        }
    }
    while(flightMenuChoice != 5);

    return 0;
}

void flightManagerMenu(){
    cout << endl << "Flight Management Menu" << endl;
    cout << "1. Add a Flight" << endl;
    cout << "2. Remove a Flight" << endl;
    cout << "3. List All Flights" << endl;
    cout << "4. Select a Flight and Manage Passengers" << endl;
    cout << "5. Exit" << endl;
}

void mainPassengerMenu(){
    cout << endl << "Passenger Management Menu" << endl;
    cout << "1. Reserve a Ticket" << endl;
    cout << "2. Cancel a Reservation" << endl;
    cout << "3. Check Reservation" << endl;
    cout << "4. Display Passengers" << endl;
    cout << "5. Back to Flight Management Menu" << endl;
}

/* use later:
if(choice == 1){
cout << "Enter Passenger's First Name:" << endl;
cin >> userName;
cout << "Enter Passenger's Last Name:" << endl;
cin >> userSurname;
cout << "Enter Passenger's Gender (M/F):" << endl;
cin >> userGender;
Passenger passenger = *new Passenger(userName, userSurname, userGender);
if(flight.reserveSeat(passenger)){
cout << "Reservation Done Successfully." << endl;
}
else{
cout << "Reservation Could Not Be Done." << endl;
}
userName = {}, userSurname = {}, userGender = {};
}
else if(choice == 2){
cout << "Enter the First Name of the Passenger Whose Reservation You Want to Cancel:\n";
cin >> userName;
cout << "Enter the Last Name of the Passenger Whose Reservation You Want to Cancel:\n";
cin >> userSurname;
flight.cancelReservation(userName, userSurname);
userName = {}, userSurname = {};
}
else if(choice == 3){
cout << "Enter Your First Name:\n";
cin >> userName;
cout << "Enter Your Last Name:\n";
cin >> userSurname;
flight.checkReservation(userName, userSurname);
userName = {}, userSurname = {};
}
else if(choice == 4){
cout << "Passenger List:\n";
flight.printPassengers();

}
else if(choice == 5){
flight.display(); //change that later...
}
else if(choice == 6){
cout << "Exiting Program.\n";
}
else{
cout << "Invalid choice.\n"; //fix the char bug!
}
*/