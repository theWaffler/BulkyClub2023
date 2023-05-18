#include "Employee.h"

Employee::Employee()
{
    // Add default users
    users.push_back(User{"admin", "admin123", EmployeeType::Admin});
    users.push_back(User{"manager", "easy", EmployeeType::Manager});
}

bool Employee::validateCredentials(const QString& username, const QString& password)
{
    // Iterate over users to find matching username
    for (const auto& user : users)
    {
        if (user.username == username && user.password == password)
            return true;
    }

    // If no match found, return false
    return false;
}
