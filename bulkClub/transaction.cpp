#include "transaction.h"

Transaction::Transaction(QDate _date, int _customerId,
                         QString _productDescription, double _price, int _quantity)
{
    date = _date;
    customerId = _customerId;
    productDescription = _productDescription;
    price = _price;
    quantity = _quantity;
}

