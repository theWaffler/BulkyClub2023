#include <QApplication>
#include "login.h"
#include "datawarehouse.h"

int main(int argc, char *argv[])
{
    DataWarehouse storage;
    storage.GetSalesReportForDate(QDate(2011,1,1), REPORT_ALL_MEMBERS); // temp for testing
    qDebug() << "test\n";

    QApplication a(argc, argv);
    login w;
    w.show();
    return a.exec();
}
