#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "Passenger.h"

using namespace std;

class Flight{
public:
    string flightNo = "THY5835";
    int passengerCounter = 0, maxSeats = 25;
    vector<Passenger> passengerVector;
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
    void checkReservation(string userSurname){
        if(Flight::searchForSurname(userSurname) == true) {
            cout << "Your Flight Number is: " << this->flightNo << endl;
        }
        else{
            cout << "You Do Not Have a Reservation." << endl;
        }
    }
    bool cancelReservation(string userSurname) {
        if(Flight::searchForSurname(userSurname)) {
            int temp = passengerCounter;
            //it doesn't actually delete the searched passenger
            passengerVector.pop_back();
            //it deletes the last passenger added to the vector. fix it!!
            if(temp > passengerVector.size()) {
                cout << "Reservation Cancelled Successfully." << endl;
                return true;
            }
            else {
                cout << "Reservation Could Not Be Canceled." << endl;
                return false;
            }
        }
        else{
            cout << "There is No Passenger With This Surname.";
            return false;
        }
    }
    int numberOfPassengers() {
        return passengerVector.size();
    }
    void printPassengers() {
        int i = 1;
        for (auto& passenger : passengerVector) {
            cout << i << ". ";
            passenger.display();
            i++;
        }
    }
    bool searchForSurname(string userSurname){
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
};

void mainMenu();

int main() {

    string userName, userSurname;
    char userGender;
    int choice = 0;

    Flight flight = *new Flight();

    do{
        mainMenu();
        cin >> choice;
        if(choice == 1){
            cout << "Please Enter Passenger Information as \"FirstName LastName M/F\" \n";
            cin >> userName;
            cin >> userSurname;
            cin >> userGender;
            Passenger passenger = *new Passenger(userName, userSurname, userGender);
            flight.reserveSeat(passenger);
            userName = {}, userSurname = {}, userGender = {};
        }
        else if(choice == 2){
            cout << "Enter the Last Name of the Passenger Whose Reservation You Want to Cancel:\n";
            cin >> userSurname;
            flight.cancelReservation(userSurname);
            userSurname = {};
        }
        else if(choice == 3){
            cout << "Enter Your Last Name to Check Your Reservation.\n";
            cin >> userSurname;
            flight.checkReservation(userSurname);
            userSurname = {};
        }
        else if(choice == 4){
            cout << "Passenger List:\n";
            flight.printPassengers();
        }
        else if(choice == 5){
            cout << "Exiting Program.\n";
        }
        else{
            cout << "Invalid choice.\n"; //fix the char bug!
        }
    }
    while(choice != 5);

    return 0;
}

void mainMenu(){
    cout << endl << "Flight Menu" << endl;
    cout << "1. Reserve a Ticket" << endl;
    cout << "2. Cancel Reservation" << endl;
    cout << "3. Check Reservation" << endl;
    cout << "4. Display Passengers" << endl;
    cout << "5. Exit" << endl;
}