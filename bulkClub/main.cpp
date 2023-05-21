#include <QApplication>
#include "login.h"
#include "datawarehouse.h"
#include "common.h"

void TestRequirements(DataWarehouse& storage);

int main(int argc, char *argv[])
{
    DataWarehouse storage;

    TestRequirements(storage);

    QApplication a(argc, argv);
    login w;
    w.show();
    return a.exec();
}

void TestRequirements(DataWarehouse& storage)
{
    QString s;

    // Requirement 1
    s = storage.GetSalesReportForDate(QDate(2021,4,5), REPORT_ALL_MEMBERS);
    qDebug() << s;

    // Requirement 2 a
    s = storage.GetSalesReportForDate(QDate(2021,4,5), REPORT_EXECUTIVE_ONLY);
    qDebug() << s;

    // Requirement 2 b
    s = storage.GetSalesReportForDate(QDate(2021,4,5), REPORT_REGULAR_ONLY);
    qDebug() << s;

    // Requirement 3
    s = storage.GetPurchasesAllMembers();
    qDebug() << s;

    // Requirement 4
    s = storage.GetItemQuantities();
    qDebug() << s;

    // Requirement 5
    s = storage.GetExecutiveRebates();
    qDebug() << s;

    // Requirement 6
    s = storage.GetMembershipExpirations(5, 2022);
    qDebug() << s;

    // Requirement 7a
    Member m("Test Member",87652, false, QDate::fromString("11/11/22", "M/d/yyyy"),0,0, false);
    storage.AddMember(m);

    // Requirmenent 7b
    int memberId = storage.GetMemberIdByName("Test Member");
    storage.DeleteMember(memberId);

    // Requirement 8
    Transaction*     t = new Transaction(QDate::fromString("11/11/21", "M/d/yyyy"), 12345, "Coke", 1.50, 1);
    storage.MakePurchase(t);

    // Requirement 9
    Item i("Test Item", 3.33, 0, false);
    storage.AddItem(i);
    storage.DeleteItem("Test Item");

    // Requirement 10
    s = storage.GetItemQuantity("Coke");
    qDebug() << s;

    // Requirement 11 a
    int n = storage.GetMemberIdByName("Larry Largefamily");
    s = storage.GetMemberPurchases(n);
    qDebug() << s;

    // Requirement 11 b
    s = storage.GetMemberPurchases(12345);
    qDebug() << s;

    // Requirement 12
    s = storage.GetConvertToExecutiveRecommendations();
    qDebug() << s;

    // Requirement 13
    s = storage.GetConvertToRegularRecommendations();
    qDebug() << s;
}
