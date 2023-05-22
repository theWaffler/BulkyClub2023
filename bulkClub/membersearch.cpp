#include "membersearch.h"
#include "ui_membersearch.h"
#include "QLabel"
#include <QMovie>
#include "datawarehouse.h"
#include <QString>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QHeaderView>
#include "mainwindow.h"
#include <QLine>
#include <QPushButton>
#include <QLineEdit>

memberSearch::memberSearch(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::memberSearch)
{
    ui->setupUi(this);
    lineEdit_memberNumberSearch = ui->lineEdit_memberNumberSearch;

    connect(ui->pushButton_memberSearchButton, &QPushButton::clicked, this, [this]() {
        QString memberName = ui->lineEdit_memberNameSearch->text();
        QString memberNumber = lineEdit_memberNumberSearch->text();
        emit searchRequested(memberName, memberNumber);
    });

}

memberSearch::~memberSearch()
{
    delete ui;
}

void memberSearch::on_pushButton_memberSearchButton_clicked()
{
    // Clear text when search button is clicked on
    // didn't work ahhh!!
    //ui->lineEdit_memberNameSearch->clear();
   // ui->lineEdit_memberNumberSearch->clear();
}
