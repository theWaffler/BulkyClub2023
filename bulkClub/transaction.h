#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "Common.h"

class Transaction
{
public:  // we can consider making this private and adding access methods later
    QDate date;
    int customerId;
    QString productDescription;
    double price;
    int quantity;
public:
    Transaction(QDate _date, int _customerId,
                QString _productDescription, double _price, int _quantity);



};

#endif // TRANSACTION_H
