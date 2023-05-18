#include <QApplication>
#include "LoginWindow.h"
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    LoginWindow loginWindow;
    MainWindow mainWindow;

    QObject::connect(&loginWindow, &LoginWindow::loginSuccessful, [&loginWindow, &mainWindow]() {
        loginWindow.hide();
        mainWindow.show();
    });

    loginWindow.show();

    return app.exec();
}
