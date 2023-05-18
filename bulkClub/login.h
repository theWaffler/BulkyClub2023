#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include "Employee.h"

namespace Ui {
class login;
}

class login : public QMainWindow
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

private slots:
    void on_pushButton_login_clicked();
    void on_pushButton_cancel_clicked();

private:
    Ui::login *ui;
    Employee *employee; // Add an Employee pointer as a member variable
};

#endif // LOGIN_H
