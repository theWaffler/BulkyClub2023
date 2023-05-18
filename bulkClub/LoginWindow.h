// LoginWindow.h

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QDebug>

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    LoginWindow(QWidget *parent = nullptr);

signals:
    void loginSuccessful();

private slots:
    void login();

private:
    QLineEdit* usernameLineEdit;
    QLineEdit* passwordLineEdit;
    QPushButton* loginButton;

    // Other GUI elements and widgets
};
