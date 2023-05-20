#ifndef ITEM_H
#define ITEM_H

#include "Common.h"

class Item
{
public: // we can consider making this private and adding access methods later
    QString product;
    double price;
    bool isDeleted;
    int numSold;



public:
    Item();
    Item(QString _product, double _price, int _numSold, bool _isDeleted = false);
};

#endif // ITEM_H
