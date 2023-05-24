#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Employee.h>
#include "datawarehouse.h"
#include "membersearch.h"
#include <QStandardItemModel>
#include <QHeaderView>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //constructor
    explicit MainWindow(EmployeeType role, QWidget *parent = nullptr);
    //destructor
    ~MainWindow();

private slots:
    void on_pushButton_searchSalesReport_clicked();
    //void on_pushButton_salesReportMemberTypeDisplay_clicked();
    void on_pushButton_itemSold_clicked();
    void on_pushButton_totalRevenueTax_clicked();
    void on_pushButton_memberShoppingDataSearch_clicked();
    //void on_pushButton_memberType_clicked();


    void on_pushButton_addItem_clicked();
    void on_pushButton_deleteItem_clicked();
    void on_pushButton_changeItemPrice_clicked();
    void on_pushButton_makePurchase_clicked();




    void on_pushButton_itemAddDelete_clicked();
    void on_pushButton_memberRebateDisplay_clicked();
    void on_pushButton_memberExpSearch_clicked();
    void on_pushButton_inventorySearch_clicked();
    void on_pushButton_memberSearch_clicked();
    void on_pushButton_addMember_clicked();
    void on_pushButton_deleteMember_clicked();
    void handleMemberSearchWindowDestroyed(QObject *obj); // slot to handle member search window closing
    void performMemberSearch(const QString& memberName, const QString& memberNumber);
    void on_pushButton_salesReportExecutive_clicked();
    void on_pushButton_salesReportRegular_clicked();
    void on_pushButton_memberConversionRegular_clicked();
    void on_pushButton_executiveRegular_clicked();

private:
    Ui::MainWindow *ui;
    DataWarehouse storage;
    memberSearch* memberSearchWindow;
    QStandardItemModel* tableModel;
    QStandardItemModel* memberSearchTableModel;
    QStandardItemModel* inventorySearchTableModel;
    QStandardItemModel* expSearchTableModel;
    QStandardItemModel* executiveRebateTableModel;
    QStandardItemModel* totalRevenue();
    QStandardItemModel* executiveSalesTableModel;
    QStandardItemModel* regularSalesTableModel;
    QStandardItemModel* allSalesTableModel;
    QStandardItemModel* memberConversionRegularModel;
    QStandardItemModel* memberConversionExecutiveModel;

    // table setup
    void setupTableModel();
    void setupTableModelExpSearch();
    void setupTableModelMemberSearch();
    void setupTableModelInventorySearch();
    void setupExecutiveRebate();
    void setupTotalRevenue();
    void setupExecutiveSalesTable();
    void setupRegularSalesTable();
    void setupAllSalesTable();
    void setupMemberConversionRegular();
    void setupMemberConversionExecutive();

    // populate table
    //void populateInventoryTable(const QString& itemData);
    void populateInventoryTable(const QStringList& itemData);
    //void populateExpMemberTable(const QVector<QString>& data);
    void populateExpMemberTable(const QStringList& data);
    void populateTable(const QVector<QString>& data);
    //void populateExecutiveRebate(const QVector<QString>& data);
    void populateExecutiveRebate(const QStringList& data);
    void populateTotalRevenue(const QStringList& data);
    void populateExecutiveSalesTable(const QStringList& data);
    void populateRegularSalesTable(const QStringList& data);
    void populateAllSalesTable(const QStringList& data);
    void populateMemberConversionRegular(const QStringList& data);
    void populateMemberConversionExecutive(const QStringList& data);
};

#endif // MAINWINDOW_H
