#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <iostream>
#include <cstring>

using namespace std;

int const MAX_SIZE=26;

class Employee
{
public:
    Employee(string user, char pass[])
        :username(user),
    {
        strncpy(password, pass, MAX_SIZE);
        password[MAX_SIZE - 1] = '\0'; // Ensure null-termination
    }

private:
    string username;
    char password[MAX_SIZE];
};

#endif // EMPLOYEE_H
