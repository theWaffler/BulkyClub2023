#include "LoginWindow.h"
#include "ui_LoginWindow.h"

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Create GUI elements
    usernameLineEdit = new QLineEdit(this);
    passwordLineEdit = new QLineEdit(this);
    loginButton = new QPushButton("Login", this);

    // Set password mode for the password line edit
    passwordLineEdit->setEchoMode(QLineEdit::Password);

    // Connect the loginButton clicked signal to the login slot
    connect(loginButton, &QPushButton::clicked, this, &LoginWindow::login);

    // Layout the GUI elements using layouts or manually set the positions and sizes

    // Other GUI setup
}

void LoginWindow::login()
{
    QString username = usernameLineEdit->text();
    QString password = passwordLineEdit->text();

    if (username == "admin" && password == "admin1")
    {
        qDebug() << "Admin login successful";
        emit loginSuccessful(); // Emit loginSuccessful signal upon successful login
    }
    else if (username == "manager" && password == "manager1")
    {
        qDebug() << "Manager login successful";
        emit loginSuccessful(); // Emit loginSuccessful signal upon successful login
    }
    else
    {
        qDebug() << "Invalid username or password";
        // Display error message or perform other actions for failed login
    }
}
