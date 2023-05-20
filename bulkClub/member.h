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
    double totalAmountSpent;
    double rebate;
    bool isDeleted;

public:
    Member();
    Member(QString _name, int _id, bool _isExecutive, QDate _expirationDate,
           double _totalAmountSpent, double _rebate, bool _isDeleted = false);
};

#endif // MEMBER_H
