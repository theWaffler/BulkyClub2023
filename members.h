#ifndef MEMBERS
#define MEMBERS
#include <iostream>
#include <fstream>

using namespace std;
// thinking two classes. One called Members and a child class called Executive. Which will inherit from the parent class 'Members'
class Members {
    public:
    // Constructor - takes 5 arguments. Initilize to default values
    Members(string n = " ", int num = 000000, string mtype =" ", double t = 0.0, string d =" ")
        : memName(n),
            memNum(num),
            memType(mtype),
            totalAmt(t), 
            expDate(d) {};

    ~Members();
    // insert methods here

    // overload operators
    //reads from file
    friend ifstream& operator>>(ifstream& ifs, Members& member);

    // prints out
    friend ostream& operator<<(ostream& os, const Members& member);

    private:
    string memName; //member name
    int memNum; // membership number
    string memType; // membership type (regular or executive)
    double totalAmt; // total amount (running total)
    string expDate; // expiration date
};
#endif
/* MEMBERS*/