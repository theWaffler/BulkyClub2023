#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QLabel"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Bulk Club");
    resize(500,400);
    QLabel *label = new QLabel(this);
    label->setText("Testing text");
}

MainWindow::~MainWindow()
{
    delete ui;
}

