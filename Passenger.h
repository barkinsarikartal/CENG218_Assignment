#pragma once
#include <string>

using namespace std;

class Passenger{
public:
    string name, surname, fullName;
    char gender;
public:
    Passenger(string userName, string userSurname, char userGender)
            : name(userName), surname(userSurname), gender(userGender) {}
public:
    void setName(string userName);
    void setSurname(string userSurname);
    void setGender(char userGender);
    void setfullName(string userName, string userSurname);
    void getName();
    void getSurname();
    void getGender();
    void getfullName();
    void display(){
        cout << this->name << " " << this->surname << " " << this->gender << endl;
    }
};