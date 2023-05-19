#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QLabel"
#include <QMovie>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Bulky Club");
    //taco gif
    QMovie *movie = new QMovie(":/images/tacoFlying.gif");
    ui->taco->setMovie(movie);
    movie->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_searchSalesReport_clicked()
{

}


void MainWindow::on_pushButton_salesReportMemberTypeDisplay_clicked()
{

}


void MainWindow::on_pushButton_itemSold_clicked()
{

}


void MainWindow::on_pushButton_totalRevenueTax_clicked()
{

}


void MainWindow::on_pushButton_memberShoppingDataSearch_clicked()
{

}


void MainWindow::on_pushButton_memberType_clicked()
{

}

