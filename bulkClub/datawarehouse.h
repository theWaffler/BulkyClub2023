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
#include <QDir>
#include <QDirIterator>

class DataWarehouse
{
private:
    vector<Member> Members;
    vector<Transaction*> Transactions;
    vector<Item> Inventory;

    void LoadMembers();
    void LoadTransactionsAndInventory();

public:
    DataWarehouse();

    void sortData();

    QString GetSalesReportForDate(QDate date, int reportType);

    QString GetPurchasesAllMembers();
    QString GetItemQuantities();
    QString GetExecutiveRebates();
    QString GetMembershipExpirations(int month, int year);
    void AddMember(Member* m);
    void DeleteMember(int memberId);
    void MakePurchase(Transaction* t);
    void AddItem(Item i);
    void DeleteItem(int itemId);
    void ChangePrice(int itemId);
    QString GetSalesInfoForItem(QString itemName);
    int GetMemberIdByName(QString memberName);
    QString GetMemberPurchases(int memberId);
    bool ShouldBeExecutive (int memberId);
    double GetMemberRebate(int memberId);
    QString GeConvertToExecutiveRecommendations();
    QString GeConvertToRegularRecommendations();
};
#endif // DATAWAREHOUSE_H
