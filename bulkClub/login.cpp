#include "login.h"
#include "ui_login.h"
#include "Employee.h"
#include <QMessageBox>
#include "mainwindow.h"
#include <QMovie>

login::login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::login)
    , employee(new Employee)  // Initialize the Employee class
{
    ui->setupUi(this);
    QMovie *movie = new QMovie(":/images/eat-yummy.gif");
    ui->logo->setMovie(movie);
    movie->start();
}

login::~login()
{
    delete ui;
    delete employee;  // Clean up the Employee class
}

void login::on_pushButton_login_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();

    if (employee->validateCredentials(username, password)) {
        // Login successful
        this->close();  // Close the login window

        EmployeeType role = employee->getUserRole(username);  // Get the user's role

        MainWindow *mainWindow = new MainWindow(role);  // Create a new MainWindow with the user's role
        mainWindow->show();  // Show the MainWindow
    } else {
        // Login failed
        // Show QMessageBox with an error message, clear password
        QMessageBox::warning(this, "Login failed", "Incorrect username or password. Please try again.");
        ui->lineEdit_password->clear();
    }
}

void login::on_pushButton_cancel_clicked()
{
    // Cancel button

    //clears username
    //ui->lineEdit_username->clear();

    //clear password
    //ui->lineEdit_password->clear();

    this->close(); //close the login window
}
