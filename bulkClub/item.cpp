#include "item.h"


Item::Item() {}
Item::Item(QString _product, double _price, int _numSold, bool _isDeleted)
{
    product = _product;
    price = _price;
    isDeleted = _isDeleted;
    numSold = _numSold;
}
