#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_searchSalesReport_clicked();

    void on_pushButton_salesReportMemberTypeDisplay_clicked();

    void on_pushButton_itemSold_clicked();

    void on_pushButton_totalRevenueTax_clicked();

    void on_pushButton_memberShoppingDataSearch_clicked();

    void on_pushButton_memberType_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
