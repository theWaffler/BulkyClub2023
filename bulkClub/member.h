#ifndef MEMBER_H
#define MEMBER_H

#include "Common.h"

class Member
{
public: // we can consider making this private and adding access methods later
    QString name;
    int id;
    bool isExecutive;
    QDate expirationDate;
    double TotalAmountSpent;
    double rebate;
    bool isDeleted;

public:
    Member();
};

#endif // MEMBER_H
