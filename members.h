#ifndef MEMBERS
#define MEMBERS
#include <iostream>
#include <fstream>

using namespace std;
// thinking two classes. One called Members and a child class called Executive. Which will inherit from the parent class 'Members'
class Members {
    public:
        // Constructor - takes 4 arguments
    Members(string n, int num, string mtype, double t)
        : memName(n),
            memNum(num),
            memType(mtype),
            totalAmt(t) {};

    ~Members();
    // insert methods here
    // overload operators

    //reads from file
    // no idea why there's a 'too many parameter error'
    ifstream& operator>>(ifstream& ifs, Members& member);

    // prints out
    friend ostream& operator<<(ostream& os, const Members& member);

    private:
    string memName; //member name
    int memNum; // membership number
    string memType; // membership type (regular or executive)
    double totalAmt; // total amount (running total)
};
#endif
/* MEMBERS*/