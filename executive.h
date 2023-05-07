#ifndef EXECUTIVE
#define EXECUTIVE

#include "members.h"
using namespace std;

class Executive : public Members {
    public:
    Executive(std::string n = "", int num = 0, std::string mtype = "", std::string expDate = "", double t = 0.0, double rb = 0.0)
        : rebate(rb) {};

    private:
    double rebate; // 2% rebate
};
#endif
/* EXECUTIVE*/