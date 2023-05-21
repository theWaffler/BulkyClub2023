#include "member.h"

Member::Member() {}
Member::Member(QString _name, int _id, bool _isExecutive, QDate _expirationDate,
               double _totalAmountSpent, double _rebate, bool _isDeleted)
{
    name = _name;
    id = _id;
    isExecutive = _isExecutive;
    expirationDate = _expirationDate;
    totalAmountSpent = _totalAmountSpent;
    rebate = _rebate;
    isDeleted = _isDeleted;
}

