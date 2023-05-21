#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QLabel"
#include <QMovie>

MainWindow::MainWindow(EmployeeType role, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Bulky Club 2023");
    //taco gif
    QMovie *movie = new QMovie(":/images/tacoFlying.gif");
    ui->taco->setMovie(movie);
    movie->start();

    if (role == EmployeeType::Admin) {
        //enable admin-specific GUI elements
        ui->pushButton_searchSalesReport->setEnabled(true);
        ui->pushButton_salesReportMemberTypeDisplay->setEnabled(true);
        ui->pushButton_itemSold->setEnabled(true);
        ui->pushButton_totalRevenueTax->setEnabled(true);
        ui->pushButton_memberShoppingDataSearch->setEnabled(true);
        ui->pushButton_memberType->setEnabled(true);
        ui->pushButton_itemAddDelete->setEnabled(true);
        ui->pushButton_memberAddDelete->setEnabled(true);
        ui->pushButton_memberRebateDisplay->setEnabled(true);
        ui->pushButton_memberExpSearch->setEnabled(true);
        ui->pushButton_inventorySearch->setEnabled(true);
        ui->pushButton_memberSearch->setEnabled(true);
    }
    else {
        //disable admin-specific GUI elements
        ui->pushButton_searchSalesReport->setEnabled(true);
        ui->pushButton_salesReportMemberTypeDisplay->setEnabled(true);
        ui->pushButton_itemSold->setEnabled(true);
        ui->pushButton_totalRevenueTax->setEnabled(true);
        ui->pushButton_memberShoppingDataSearch->setEnabled(true);
        ui->pushButton_memberType->setEnabled(true);
        ui->pushButton_itemAddDelete->setEnabled(false);
        ui->pushButton_memberAddDelete->setEnabled(false);
        ui->pushButton_memberRebateDisplay->setEnabled(true);
        ui->pushButton_memberExpSearch->setEnabled(true);
        ui->pushButton_inventorySearch->setEnabled(true);
        ui->pushButton_memberSearch->setEnabled(true);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_searchSalesReport_clicked()
{
// Manager function
}


void MainWindow::on_pushButton_salesReportMemberTypeDisplay_clicked()
{
// Manager function
}


void MainWindow::on_pushButton_itemSold_clicked()
{
// Manager function
}


void MainWindow::on_pushButton_totalRevenueTax_clicked()
{
// Manager function
}


void MainWindow::on_pushButton_memberShoppingDataSearch_clicked()
{
// Manager function
}


void MainWindow::on_pushButton_memberType_clicked()
{
// Manager function
}


void MainWindow::on_pushButton_itemAddDelete_clicked()
{
//ADMIN function
}


void MainWindow::on_pushButton_memberAddDelete_clicked()
{
//ADMIN function
}


void MainWindow::on_pushButton_memberRebateDisplay_clicked()
{
// Manager function
}


void MainWindow::on_pushButton_memberExpSearch_clicked()
{
// Manager function
}


void MainWindow::on_pushButton_inventorySearch_clicked()
{
// Manager function
}


void MainWindow::on_pushButton_memberSearch_clicked()
{
// Manager function
}

