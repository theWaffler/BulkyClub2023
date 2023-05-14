#ifndef DATAWAREHOUSE_H
#define DATAWAREHOUSE_H

#include "member.h"
#include "transaction.h"
#include "item.h"
#include <map>

struct CompositeKey {
    QDate date;
    int buyerId;
    QString itemName;
    bool operator<(const CompositeKey& other) const {
        if (date < other.date) return true;
        if (date > other.date) return false;
        if (buyerId < other.buyerId) return true;
        if (buyerId > other.buyerId) return false;
        return itemName < other.itemName;
    }
};

class DataWarehouse
{
private:
    map<int, Member> members; // key is member id
    multimap<CompositeKey, Transaction*> transactions;
   // map<int, Item> items; // todo: we don't have list of items, need to ask professor.
                            // i.e. will there be an item id that we can use for a key?
    void LoadMembers();
    void LoadTransactions();
    void LoadInventory();

public:
    DataWarehouse();

    // We can move this to a Manager/Adminstrator class if we want
    QString GetSalesReportForDate(QDate date);
    QString GetSalesReportForMembershipType(bool isExecutive);
    QString GetAllPurchases();
    QString GetItemQuantities();
    QString GetExecutiveRebates();
    QString GetMembershipExpirations(QDate month);
    void AddMember(Member & m);
    void DeleteMember(int memberId);
    void MakePurchase(Transaction* t);
    void AddItem(Item i);
    void DeleteItem(int itemId);
    void ChangePrice(int itemId);
    QString GetSalesInfoForItem(QString itemName);
    int GetMemberIdByName(QString memberName);
    QString GetTotalPurchases(int memberId);
    bool ShouldBeExecutive (int memberId);
    bool ShouldBeRegularMember(int memberId);

};
#endif // DATAWAREHOUSE_H
