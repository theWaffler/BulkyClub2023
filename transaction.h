#ifndef TRANSACTION
#define TRANSACTION

#include "members.h"
using namespace std;

class Transaction  
{
public:
    Transaction(string _date, int _customerId, 
    string _productDescription, double _price, int _quantity)
    {
        date = _date;
        customerId = _customerId;
        productDescription = _productDescription;
        price = _price;
        quantity = _quantity;
    }

private:
    string date;
    int customerId;
    string productDescription;
    double price;
    int quantity;
};
#endif
/* TRANSACTION*/