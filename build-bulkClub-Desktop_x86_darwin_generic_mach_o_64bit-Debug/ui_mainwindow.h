/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *taco;
    QLineEdit *lineEdit_memberShoppingData;
    QLabel *label_memberShoppingDataDate;
    QLabel *label_salesReportMemberType;
    QLabel *label_memberShoppingData;
    QTableView *tableView;
    QLabel *label_salesDate;
    QLabel *label_salesReport;
    QPushButton *pushButton_memberShoppingDataSearch;
    QPushButton *pushButton_totalRevenueTax;
    QScrollBar *verticalScrollBar;
    QLabel *label_totalRevenueTax;
    QPushButton *pushButton_memberType;
    QPushButton *pushButton_salesReportMemberTypeDisplay;
    QPushButton *pushButton_searchSalesReport;
    QPushButton *pushButton_itemSold;
    QRadioButton *radioButton_regular;
    QLineEdit *lineEdit_dateSalesReport;
    QLabel *label;
    QRadioButton *radioButton_executive;
    QLabel *label_memberType;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1280, 720);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        taco = new QLabel(centralwidget);
        taco->setObjectName("taco");
        taco->setGeometry(QRect(870, 140, 401, 371));
        taco->setPixmap(QPixmap(QString::fromUtf8(":/image/D:/School/CS-1C/GroupProject/cs1c_proj/bulkClub/tacoFlying.gif")));
        lineEdit_memberShoppingData = new QLineEdit(centralwidget);
        lineEdit_memberShoppingData->setObjectName("lineEdit_memberShoppingData");
        lineEdit_memberShoppingData->setGeometry(QRect(90, 430, 150, 30));
        label_memberShoppingDataDate = new QLabel(centralwidget);
        label_memberShoppingDataDate->setObjectName("label_memberShoppingDataDate");
        label_memberShoppingDataDate->setGeometry(QRect(10, 440, 49, 16));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        label_memberShoppingDataDate->setFont(font);
        label_salesReportMemberType = new QLabel(centralwidget);
        label_salesReportMemberType->setObjectName("label_salesReportMemberType");
        label_salesReportMemberType->setGeometry(QRect(10, 120, 291, 31));
        QFont font1;
        font1.setPointSize(15);
        font1.setBold(true);
        label_salesReportMemberType->setFont(font1);
        label_memberShoppingData = new QLabel(centralwidget);
        label_memberShoppingData->setObjectName("label_memberShoppingData");
        label_memberShoppingData->setGeometry(QRect(10, 390, 251, 41));
        label_memberShoppingData->setFont(font1);
        tableView = new QTableView(centralwidget);
        tableView->setObjectName("tableView");
        tableView->setGeometry(QRect(310, 20, 531, 641));
        label_salesDate = new QLabel(centralwidget);
        label_salesDate->setObjectName("label_salesDate");
        label_salesDate->setGeometry(QRect(20, 40, 49, 16));
        label_salesDate->setFont(font);
        label_salesReport = new QLabel(centralwidget);
        label_salesReport->setObjectName("label_salesReport");
        label_salesReport->setGeometry(QRect(20, 10, 121, 21));
        label_salesReport->setFont(font1);
        pushButton_memberShoppingDataSearch = new QPushButton(centralwidget);
        pushButton_memberShoppingDataSearch->setObjectName("pushButton_memberShoppingDataSearch");
        pushButton_memberShoppingDataSearch->setGeometry(QRect(160, 460, 80, 30));
        QFont font2;
        font2.setPointSize(12);
        pushButton_memberShoppingDataSearch->setFont(font2);
        pushButton_totalRevenueTax = new QPushButton(centralwidget);
        pushButton_totalRevenueTax->setObjectName("pushButton_totalRevenueTax");
        pushButton_totalRevenueTax->setGeometry(QRect(10, 340, 80, 30));
        pushButton_totalRevenueTax->setFont(font2);
        verticalScrollBar = new QScrollBar(centralwidget);
        verticalScrollBar->setObjectName("verticalScrollBar");
        verticalScrollBar->setGeometry(QRect(850, 30, 20, 621));
        verticalScrollBar->setOrientation(Qt::Vertical);
        label_totalRevenueTax = new QLabel(centralwidget);
        label_totalRevenueTax->setObjectName("label_totalRevenueTax");
        label_totalRevenueTax->setGeometry(QRect(10, 310, 231, 31));
        label_totalRevenueTax->setFont(font1);
        pushButton_memberType = new QPushButton(centralwidget);
        pushButton_memberType->setObjectName("pushButton_memberType");
        pushButton_memberType->setGeometry(QRect(10, 550, 80, 30));
        pushButton_memberType->setFont(font2);
        pushButton_salesReportMemberTypeDisplay = new QPushButton(centralwidget);
        pushButton_salesReportMemberTypeDisplay->setObjectName("pushButton_salesReportMemberTypeDisplay");
        pushButton_salesReportMemberTypeDisplay->setGeometry(QRect(100, 160, 80, 30));
        pushButton_salesReportMemberTypeDisplay->setFont(font2);
        pushButton_searchSalesReport = new QPushButton(centralwidget);
        pushButton_searchSalesReport->setObjectName("pushButton_searchSalesReport");
        pushButton_searchSalesReport->setGeometry(QRect(150, 80, 80, 30));
        QFont font3;
        font3.setPointSize(12);
        font3.setBold(false);
        pushButton_searchSalesReport->setFont(font3);
        pushButton_itemSold = new QPushButton(centralwidget);
        pushButton_itemSold->setObjectName("pushButton_itemSold");
        pushButton_itemSold->setGeometry(QRect(10, 270, 80, 30));
        pushButton_itemSold->setFont(font2);
        radioButton_regular = new QRadioButton(centralwidget);
        radioButton_regular->setObjectName("radioButton_regular");
        radioButton_regular->setGeometry(QRect(10, 180, 89, 20));
        QFont font4;
        font4.setPointSize(10);
        radioButton_regular->setFont(font4);
        lineEdit_dateSalesReport = new QLineEdit(centralwidget);
        lineEdit_dateSalesReport->setObjectName("lineEdit_dateSalesReport");
        lineEdit_dateSalesReport->setGeometry(QRect(80, 40, 150, 30));
        lineEdit_dateSalesReport->setFont(font2);
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 240, 111, 31));
        label->setFont(font1);
        radioButton_executive = new QRadioButton(centralwidget);
        radioButton_executive->setObjectName("radioButton_executive");
        radioButton_executive->setGeometry(QRect(10, 160, 89, 20));
        radioButton_executive->setFont(font4);
        label_memberType = new QLabel(centralwidget);
        label_memberType->setObjectName("label_memberType");
        label_memberType->setGeometry(QRect(10, 510, 251, 41));
        label_memberType->setFont(font1);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1280, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        taco->setText(QString());
        label_memberShoppingDataDate->setText(QCoreApplication::translate("MainWindow", "Date:", nullptr));
        label_salesReportMemberType->setText(QCoreApplication::translate("MainWindow", "Sales Report by Member Type", nullptr));
        label_memberShoppingData->setText(QCoreApplication::translate("MainWindow", "Members Shopping Data", nullptr));
        label_salesDate->setText(QCoreApplication::translate("MainWindow", "Date:", nullptr));
        label_salesReport->setText(QCoreApplication::translate("MainWindow", "Sales Report", nullptr));
        pushButton_memberShoppingDataSearch->setText(QCoreApplication::translate("MainWindow", "Search", nullptr));
        pushButton_totalRevenueTax->setText(QCoreApplication::translate("MainWindow", "Display", nullptr));
        label_totalRevenueTax->setText(QCoreApplication::translate("MainWindow", "Total Revenue (inc. tax)", nullptr));
        pushButton_memberType->setText(QCoreApplication::translate("MainWindow", "Display", nullptr));
        pushButton_salesReportMemberTypeDisplay->setText(QCoreApplication::translate("MainWindow", "Display", nullptr));
        pushButton_searchSalesReport->setText(QCoreApplication::translate("MainWindow", "Search", nullptr));
        pushButton_itemSold->setText(QCoreApplication::translate("MainWindow", "Display", nullptr));
        radioButton_regular->setText(QCoreApplication::translate("MainWindow", "Regular", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Items Sold", nullptr));
        radioButton_executive->setText(QCoreApplication::translate("MainWindow", "Executive", nullptr));
        label_memberType->setText(QCoreApplication::translate("MainWindow", "Member Type (QTY)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
