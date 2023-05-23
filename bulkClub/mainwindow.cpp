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

    // Connect the search button clicked signal to the slot
    connect(ui->pushButton_memberExpSearch, &QPushButton::clicked, this, &MainWindow::on_pushButton_memberExpSearch_clicked);

    // Create an instance of membersearch window
    memberSearchWindow = new memberSearch();

    // Connect the destroyed() signal to handleMemberSearchWindowDestroyed() slot
    connect(memberSearchWindow, &QObject::destroyed, this, &MainWindow::handleMemberSearchWindowDestroyed);

    // Connect the searchRequested signal from memberSearch to performMemberSearch slot in MainWindow
    connect(memberSearchWindow, &memberSearch::searchRequested, this, &MainWindow::performMemberSearch);

    // Set up the table model
    //setupTableModel();
    setupTableModelMemberSearch();
    setupTableModelInventorySearch();
    setupTableModelExpSearch();
    setupExecutiveRebate();
    setupTotalRevenue();
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

////////////////////////////////////////////////////////////////////////////////////////
// Total Revenue
// input: none
void MainWindow::on_pushButton_totalRevenueTax_clicked()
{
    // call datawarehouse function
    QString totalRevenue = storage.GetItemQuantities();

    //split
    QStringList rows = totalRevenue.split('\n', Qt::SkipEmptyParts);

    // call populate totalRevenue
    populateTotalRevenue(rows);
}

void MainWindow::setupTotalRevenue()
{
    //create table
    tableModel = new QStandardItemModel(this);

    //set column count and header label
    int columnCount = 1;
    tableModel->setColumnCount(columnCount);
    tableModel->setHorizontalHeaderLabels({"Search Results"});

    // set table model for table view
    ui->tableView->setModel(tableModel);

    //adjust column widths to fit content
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

void MainWindow::populateTotalRevenue(const QStringList& data)
{
    //clear existing data in table view
    tableModel->removeRows(0,tableModel->rowCount());

    // set row and column count
    int numRows = data.size();
    int numCols = 1;

    // set the model size
    tableModel->setRowCount(numRows);
    tableModel->setColumnCount(numCols);

    // Populate the table model with the rebate data
    for (int row = 0; row < numRows; ++row)
    {
        tableModel->setData(tableModel->index(row, 0), data[row].trimmed());
    }

    // Expand the height of the rows
    for (int row = 0; row < numRows; ++row)
    {
        ui->tableView->setRowHeight(row, 100); // Set the desired height in pixels
    }
}

////////////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////////////
// Display executive member rebate
// input: none

void MainWindow::on_pushButton_memberRebateDisplay_clicked()
{
    // Call the DataWarehouse function to get the executive members' rebates
    QString rebateData = storage.GetExecutiveRebates();

    // Split the rebate data into rows
    QStringList rows = rebateData.split('\n', Qt::SkipEmptyParts);

    // Call the populateExecutiveRebate function to display the rebate data in the table view
    populateExecutiveRebate(rows);
}

void MainWindow::setupExecutiveRebate()
{
    // Create the table model
    tableModel = new QStandardItemModel(this);

    // Set the column count and header labels
    int columnCount = 1;
    tableModel->setColumnCount(columnCount);
    tableModel->setHorizontalHeaderLabels({"Search Results"});

    // Set the table model for the table view
    ui->tableView->setModel(tableModel);

    // Adjust the column widths to fit the contents
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

void MainWindow::populateExecutiveRebate(const QStringList& data)
{
    // Clear the existing data in the table model
    tableModel->removeRows(0, tableModel->rowCount());

    // Set the row count and column count
    int numRows = data.size();
    int numCols = 1;

    // Set the table model size
    tableModel->setRowCount(numRows);
    tableModel->setColumnCount(numCols);

    // Populate the table model with the rebate data
    for (int row = 0; row < numRows; ++row)
    {
        tableModel->setData(tableModel->index(row, 0), data[row].trimmed());
    }

    // Expand the height of the rows
    for (int row = 0; row < numRows; ++row)
    {
        ui->tableView->setRowHeight(row, 100); // Set the desired height in pixels
    }
}
////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
// Member Expiration Search
// input: MM/YYYY

void MainWindow::on_pushButton_memberExpSearch_clicked()
{
    // Get the entered month and year from lineEdit_membeExpSearch
    QString dateStr = ui->lineEdit_membeExpSearch->text();
    QStringList dateParts = dateStr.split("/");
    if (dateParts.size() != 2)
    {
        QMessageBox::warning(this, "Invalid Date", "Please enter the month and year in the format 'month/year'.");
        return;
    }

    int month = dateParts[0].toInt();
    int year = dateParts[1].toInt();

    // Call the DataWarehouse function to get the membership expirations
    QString searchResults = storage.GetMembershipExpirations(month, year);

    // Split the search results into rows
    //QStringList rows = searchResults.split('\n');
    QStringList rows = searchResults.split('\n', Qt::SkipEmptyParts);

    // Remove the empty lines
    //rows.removeAll("");

    // Populate the table view with the search results
    populateExpMemberTable(rows);
}

void MainWindow::setupTableModelExpSearch()
{
    // Create the table model
    tableModel = new QStandardItemModel(this);

    // Set the column count and header labels
    int columnCount = 1;
    tableModel->setColumnCount(columnCount);
    tableModel->setHorizontalHeaderLabels({"Search Results"});

    // Set the table model for the table view
    ui->tableView->setModel(tableModel);

    // Adjust the column widths to fit the contents
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

void MainWindow::populateExpMemberTable(const QStringList& data)
{
    // Clear the existing data in the table model
    tableModel->removeRows(0, tableModel->rowCount());

    int numRows= data.size();
    int numCols = 1;

    //set table model size
    tableModel->setRowCount(numRows);
    tableModel->setColumnCount(numCols);

    // Populate the table model with the rebate data
    for (int row = 0; row < numRows; ++row)
    {
        tableModel->setData(tableModel->index(row, 0), data[row].trimmed());
    }

    // Expand the height of the rows
    for (int row = 0; row < numRows; ++row)
    {
        ui->tableView->setRowHeight(row, 100); // Set the desired height in pixels
    }

}
////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
// Inventory Product Search
// input: product name
void MainWindow::on_pushButton_inventorySearch_clicked()
{
    // Get the item name from lineEdit_inventorySearch
    QString itemName = ui->lineEdit_inventorySearch->text();

    // Check if the item name is empty
    if (itemName.isEmpty())
    {
        QMessageBox::warning(this, "Empty Item Name", "Please enter an item name.");
        return;
    }

    // Call DataWareHouse function
    QString itemData = storage.GetItemQuantity(itemName);

    // Split
    QStringList rows = itemData.split('\n', Qt::SkipEmptyParts);

    // call populateInventoryTable function to display data in tablebiew
    populateInventoryTable(rows);
}

void MainWindow::setupTableModelInventorySearch()
{
    //create table
    tableModel = new QStandardItemModel(this);

    // set column count and header label
    int columnCount =1;
    tableModel->setColumnCount(columnCount);
    tableModel->setHorizontalHeaderLabels({"Search Results"});

    // Set the table model for the table view
    ui->tableView->setModel(tableModel);

    // Adjust the column widths to fit the contents
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

void MainWindow::populateInventoryTable(const QStringList& itemData)
{
    // Clear the existing data in the table model
    tableModel->removeRows(0, tableModel->rowCount());

    // Set the row count and column count
    int numRows = itemData.size();
    int numCols = 1;

    // Set the table model size
    tableModel->setRowCount(numRows);
    tableModel->setColumnCount(numCols);

    // Populate the table model with the rebate data
    for (int row = 0; row < numRows; ++row)
    {
        tableModel->setData(tableModel->index(row, 0), itemData[row].trimmed());
    }

    // Expand the height of the rows
    for (int row = 0; row < numRows; ++row)
    {
        ui->tableView->setRowHeight(row, 100); // Set the desired height in pixels
    }

}
////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
// Member Search
// input: member name / member number
void MainWindow::on_pushButton_memberSearch_clicked()
{
    // Open the membersearch window
    memberSearchWindow->show();

    // Set up the table model for member search
    setupTableModelMemberSearch();
}

void MainWindow::performMemberSearch(const QString& memberName, const QString& memberNumber)
{
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

void MainWindow::setupTableModelMemberSearch()
{
    // Create the table model for member search
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
////////////////////////////////////////////////////////////////////////////////////////
