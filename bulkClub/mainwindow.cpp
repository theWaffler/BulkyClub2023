#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QLabel"
#include <QMovie>
#include "datawarehouse.h"
#include <QString>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QHeaderView>
#include "membersearch.h"
#include "ui_membersearch.h"

MainWindow::MainWindow(EmployeeType role, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Bulky Club 2023");
    //taco gif
    QMovie *movie = new QMovie(":/images/tacoFlying.gif");
    ui->taco->setMovie(movie);
    movie->start();

    if (role == EmployeeType::Admin) {
        //enable admin-specific GUI elements
        ui->pushButton_searchSalesReport->setEnabled(true);
        ui->pushButton_salesReportMemberTypeDisplay->setEnabled(true);
        ui->pushButton_itemSold->setEnabled(true);
        ui->pushButton_totalRevenueTax->setEnabled(true);
        ui->pushButton_memberShoppingDataSearch->setEnabled(true);
        ui->pushButton_memberType->setEnabled(true);
        ui->pushButton_itemAddDelete->setEnabled(true);
        ui->pushButton_memberAddDelete->setEnabled(true);
        ui->pushButton_memberRebateDisplay->setEnabled(true);
        ui->pushButton_memberExpSearch->setEnabled(true);
        ui->pushButton_inventorySearch->setEnabled(true);
        ui->pushButton_memberSearch->setEnabled(true);
    }
    else {
        //disable admin-specific GUI elements
        ui->pushButton_searchSalesReport->setEnabled(true);
        ui->pushButton_salesReportMemberTypeDisplay->setEnabled(true);
        ui->pushButton_itemSold->setEnabled(true);
        ui->pushButton_totalRevenueTax->setEnabled(true);
        ui->pushButton_memberShoppingDataSearch->setEnabled(true);
        ui->pushButton_memberType->setEnabled(true);
        ui->pushButton_itemAddDelete->setEnabled(false);
        ui->pushButton_memberAddDelete->setEnabled(false);
        ui->pushButton_memberRebateDisplay->setEnabled(true);
        ui->pushButton_memberExpSearch->setEnabled(true);
        ui->pushButton_inventorySearch->setEnabled(true);
        ui->pushButton_memberSearch->setEnabled(true);
    }

    // Create an instance of membersearch window
    memberSearchWindow = new memberSearch();

    // Connect the destroyed() signal to handleMemberSearchWindowDestroyed() slot
    connect(memberSearchWindow, &QObject::destroyed, this, &MainWindow::handleMemberSearchWindowDestroyed);

    // Connect the searchRequested signal from memberSearch to performMemberSearch slot in MainWindow
    connect(memberSearchWindow, &memberSearch::searchRequested, this, &MainWindow::performMemberSearch);

    // Set up the table model
    setupTableModel();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleMemberSearchWindowDestroyed(QObject *obj)
{
    if (obj == memberSearchWindow)
    {
        memberSearchWindow = nullptr;
    }
}

void MainWindow::on_pushButton_searchSalesReport_clicked()
{
    QString dateStr = ui->lineEdit_dateSalesReport->text();
    QDate date = QDate::fromString(dateStr, "yyyy-MM-dd");

    // Check if the entered date is valid
    if (!date.isValid())
    {
        QMessageBox::warning(this, "Invalid Date", "Please enter a valid date in the format yyyy-MM-dd.");
        return;
    }

    int reportType = REPORT_ALL_MEMBERS;  // Set the appropriate report type

    QString s = storage.GetSalesReportForDate(date, reportType);
    qDebug() << s;

    // Split the sales report data into rows
    QStringList rows = s.split('\n');

    // Get the number of rows and columns
    int numRows = rows.size();
    int numCols = 1; // Assuming one column for the sales report data

    // Create a table model for the sales report data
    QStandardItemModel *model = new QStandardItemModel(numRows, numCols, this);

    // Populate the table model with the sales report data
    for (int row = 0; row < numRows; ++row)
    {
        QString rowData = rows[row];
        QStandardItem *item = new QStandardItem(rowData);
        model->setItem(row, 0, item);
    }

    // Set the table model for the QTableView
    ui->tableView->setModel(model);

    // Set the header text for the column
    model->setHeaderData(0, Qt::Horizontal, "Sales Report");

    // Resize the columns to fit the content
    ui->tableView->resizeColumnsToContents();
}


void MainWindow::on_pushButton_salesReportMemberTypeDisplay_clicked()
{
// Testing function
// Manager function
}


void MainWindow::on_pushButton_itemSold_clicked()
{
// Manager function
}


void MainWindow::on_pushButton_totalRevenueTax_clicked()
{
// Manager function
}


void MainWindow::on_pushButton_memberShoppingDataSearch_clicked()
{
// Manager function
}


void MainWindow::on_pushButton_memberType_clicked()
{
// Manager function
}


void MainWindow::on_pushButton_itemAddDelete_clicked()
{
//ADMIN function
}


void MainWindow::on_pushButton_memberAddDelete_clicked()
{
//ADMIN function
}


void MainWindow::on_pushButton_memberRebateDisplay_clicked()
{
// Manager function
}


void MainWindow::on_pushButton_memberExpSearch_clicked()
{
// Manager function
}


void MainWindow::on_pushButton_inventorySearch_clicked()
{
// Manager function
}


void MainWindow::on_pushButton_memberSearch_clicked()
{
    // Open the membersearch window
    memberSearchWindow->show();

}

void MainWindow::performMemberSearch(const QString& memberName, const QString& memberNumber)
{
    // valid code but ugly af
    /*
    int memberId = storage.GetMemberIdByName(memberName);
    if (memberId != -1)
    {
        QString memberPurchases = storage.GetMemberPurchases(memberId);
        QVector<QString> searchData;
        searchData.append(memberName);
        searchData.append(QString::number(memberId));
        searchData.append(memberPurchases);
        populateTable(searchData);
    }
    else
    {
        QMessageBox::warning(this, "Member Not Found", "The member could not be found.");
    }
    */

    int memberId = -1;

    // Check if the member number is provided
    if (!memberNumber.isEmpty()) {
        memberId = memberNumber.toInt();
    } else {
        memberId = storage.GetMemberIdByName(memberName);
    }

    // Perform the search based on the member ID
    if (memberId != -1) {
        QString foundMemberName = storage.GetMemberNameById(memberId);
        if (!foundMemberName.isEmpty()) {
            QString memberPurchases = storage.GetMemberPurchases(memberId);
            QVector<QString> searchData;
            searchData.append(foundMemberName);
            searchData.append(QString::number(memberId));
            searchData.append(memberPurchases);
            populateTable(searchData);
            return;
        }
    }

    QMessageBox::warning(this, "Member Not Found", "The member could not be found.");
}

void MainWindow::setupTableModel()
{
    // Create the table model
    tableModel = new QStandardItemModel(this);

    // Set the column count and header labels
    int columnCount = 3;
    tableModel->setColumnCount(columnCount);
    tableModel->setHorizontalHeaderLabels({"Member Name", "Member Number", "Purchases"});

    // Set the table model for the table view
    ui->tableView->setModel(tableModel);

    // Adjust the column widths to fit the contents
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}


void MainWindow::populateTable(const QVector<QString>& data)
{

    // Clear the existing data in the table model
    tableModel->removeRows(0, tableModel->rowCount());

    // Add a new row with the data
    tableModel->insertRow(0);
    for (int i = 0; i < data.size(); ++i)
    {
        tableModel->setData(tableModel->index(0, i), data[i]);
    }
    // Expand the height of the first row
    ui->tableView->setRowHeight(0, 100); // Set the desired height in pixels

}

