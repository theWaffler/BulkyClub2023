#ifndef MEMBERS
#define MEMBERS
#include <iostream>

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

    private:
    string memName; //member name
    int memNum; // membership number
    string memType; // membership type (regular or executive)
    double totalAmt; // total amount (running total)
};
#endif
/* MEMBERS*/