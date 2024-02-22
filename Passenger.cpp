#include "Passenger.h"
#include <iostream>

using namespace std;

void Passenger::setName(string userName){
    this->name = userName;
}
void Passenger::setSurname(string userSurname){
    this->surname = userSurname;
}
void Passenger::setGender(char userGender){
    this->gender = userGender;
}
void Passenger::setfullName(string userName, string userSurname){
    this->fullName = userName + " " + userSurname;
}
void Passenger::getName(){
    cout << this->name << endl;
}
void Passenger::getSurname(){
    cout << this->surname << endl;
}
void Passenger::getGender(){
    cout << this->gender << endl;
}
void Passenger::getfullName(){
    cout << this->fullName << endl;
}
/*
void Passenger::display(){
    cout << this->name << " " << this->surname << " " << this->gender << endl;
}
*/