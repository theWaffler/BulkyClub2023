#ifndef DATAWAREHOUSE_H
#define DATAWAREHOUSE_H

#include "member.h"
#include "transaction.h"
#include "item.h"

#include <vector>
#include <algorithm>

#include <QFile>
#include <QResource>
#include <QTextStream>
#include <QRegularExpression>

class DataWarehouse
{
private:
    vector<Member> Members;
    vector<Transaction*> transactions;
    vector<Item> Inventory;

    void LoadMembers();
    void LoadTransactions();
    void LoadInventory();

public:
    DataWarehouse();

    void sortData();

    QString GetSalesReportForDate(QDate date, int reportType);

    QString GetAllPurchases();
    QString GetItemQuantities();
    QString GetExecutiveRebates();
    QString GetMembershipExpirations(QDate month);
    void AddMember(Member* m);
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
