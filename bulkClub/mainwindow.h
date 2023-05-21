#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Employee.h>

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
    void on_pushButton_salesReportMemberTypeDisplay_clicked();
    void on_pushButton_itemSold_clicked();
    void on_pushButton_totalRevenueTax_clicked();
    void on_pushButton_memberShoppingDataSearch_clicked();
    void on_pushButton_memberType_clicked();
    void on_pushButton_itemAddDelete_clicked();
    void on_pushButton_memberAddDelete_clicked();

    void on_pushButton_memberRebateDisplay_clicked();

    void on_pushButton_memberExpSearch_clicked();

    void on_pushButton_inventorySearch_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
