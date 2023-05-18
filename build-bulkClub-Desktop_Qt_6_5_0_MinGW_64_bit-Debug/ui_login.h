/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_login
{
public:
    QLabel *label_username;
    QLabel *label_password;
    QLineEdit *lineEdit_username;
    QLineEdit *lineEdit_password;
    QPushButton *pushButton_login;
    QPushButton *pushButton_cancel;
    QLabel *label_title;
    QLabel *logo;

    void setupUi(QWidget *login)
    {
        if (login->objectName().isEmpty())
            login->setObjectName("login");
        login->resize(968, 661);
        label_username = new QLabel(login);
        label_username->setObjectName("label_username");
        label_username->setGeometry(QRect(270, 290, 141, 61));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        label_username->setFont(font);
        label_password = new QLabel(login);
        label_password->setObjectName("label_password");
        label_password->setGeometry(QRect(280, 360, 131, 31));
        label_password->setFont(font);
        lineEdit_username = new QLineEdit(login);
        lineEdit_username->setObjectName("lineEdit_username");
        lineEdit_username->setGeometry(QRect(440, 310, 200, 30));
        lineEdit_password = new QLineEdit(login);
        lineEdit_password->setObjectName("lineEdit_password");
        lineEdit_password->setGeometry(QRect(440, 360, 200, 30));
        lineEdit_password->setEchoMode(QLineEdit::Password);
        pushButton_login = new QPushButton(login);
        pushButton_login->setObjectName("pushButton_login");
        pushButton_login->setGeometry(QRect(540, 410, 100, 50));
        pushButton_login->setFont(font);
        pushButton_cancel = new QPushButton(login);
        pushButton_cancel->setObjectName("pushButton_cancel");
        pushButton_cancel->setGeometry(QRect(540, 470, 100, 50));
        pushButton_cancel->setFont(font);
        label_title = new QLabel(login);
        label_title->setObjectName("label_title");
        label_title->setGeometry(QRect(380, 190, 281, 91));
        QFont font1;
        font1.setPointSize(40);
        font1.setBold(true);
        label_title->setFont(font1);
        logo = new QLabel(login);
        logo->setObjectName("logo");
        logo->setGeometry(QRect(160, 60, 211, 261));
        logo->setPixmap(QPixmap(QString::fromUtf8(":/images/eat-yummy.gif")));

        retranslateUi(login);

        QMetaObject::connectSlotsByName(login);
    } // setupUi

    void retranslateUi(QWidget *login)
    {
        login->setWindowTitle(QCoreApplication::translate("login", "Form", nullptr));
        label_username->setText(QCoreApplication::translate("login", "Username:", nullptr));
        label_password->setText(QCoreApplication::translate("login", "Password:", nullptr));
        pushButton_login->setText(QCoreApplication::translate("login", "Login", nullptr));
        pushButton_cancel->setText(QCoreApplication::translate("login", "Cancel", nullptr));
        label_title->setText(QCoreApplication::translate("login", "Bulky Club", nullptr));
        logo->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class login: public Ui_login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
