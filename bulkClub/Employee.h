#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <vector>
#include <QString>

enum class EmployeeType {
    Admin,
    Manager
};

struct User {
    QString username;
    QString password;
    EmployeeType type;
};

class Employee
{
public:
    Employee();
    bool validateCredentials(const QString& username, const QString& password);
    EmployeeType getUserRole(const QString& username)const;

private:
    std::vector<User> users;
};

#endif // EMPLOYEE_H
