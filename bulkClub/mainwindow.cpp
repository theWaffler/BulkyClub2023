#include "mainwindow.h"
#include "ItemAddDialog.h"
#include "DeleteItemDialog.h"
#include "ChangeItemPriceDialog.h""
#include "DeleteMemberDialog.h"
#include "AddMemberDialog.h"
#include "DeleteMemberDialog.h"
#include "qboxlayout.h"
#include "ui_mainwindow.h"
#include "QLabel"
#include <QMovie>
#include "datawarehouse.h"
#include <QString>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QHeaderView>
#include "membersearch.h"
//#include "ui_membersearch.h"

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
        ui->pushButton_salesReportExecutive->setEnabled(true);
        ui->pushButton_salesReportRegular->setEnabled(true);
        ui->pushButton_itemSold->setEnabled(true);
        ui->pushButton_totalRevenueTax->setEnabled(true);
        //ui->pushButton_memberShoppingDataSearch->setEnabled(true);
        //ui->pushButton_memberType->setEnabled(true);
        ui->pushButton_memberConversionRegular->setEnabled(true);
        ui->pushButton_itemAddDelete->setEnabled(true);
        ui->pushButton_memberAddDelete->setEnabled(true);
        ui->pushButton_memberRebateDisplay->setEnabled(true);
        ui->pushButton_memberExpSearch->setEnabled(true);
        ui->pushButton_inventorySearch->setEnabled(true);
        ui->pushButton_memberSearch->setEnabled(true);
        ui->pushButton_executiveRegular->setEnabled(true);
    }
    else {
        //disable admin-specific GUI elements
        ui->pushButton_searchSalesReport->setEnabled(true);
        ui->pushButton_salesReportExecutive->setEnabled(true);
        ui->pushButton_salesReportRegular->setEnabled(true);
        ui->pushButton_itemSold->setEnabled(true);
        ui->pushButton_totalRevenueTax->setEnabled(true);
        //ui->pushButton_memberShoppingDataSearch->setEnabled(true);
        //ui->pushButton_memberType->setEnabled(true);
        ui->pushButton_memberConversionRegular->setEnabled(true);
        ui->pushButton_itemAddDelete->setEnabled(false);
        ui->pushButton_memberAddDelete->setEnabled(false);
        ui->pushButton_memberRebateDisplay->setEnabled(true);
        ui->pushButton_memberExpSearch->setEnabled(true);
        ui->pushButton_inventorySearch->setEnabled(true);
        ui->pushButton_memberSearch->setEnabled(true);
        ui->pushButton_executiveRegular->setEnabled(false);
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
    //executiveSalesTableModel();
    //regularSalesTableModel();
    setupAllSalesTable();
    setupMemberConversionRegular();
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

////////////////////////////////////////////////////////////////////////////////////////
// Display sales report for ALL
// input: none
void MainWindow::on_pushButton_itemSold_clicked()
{
    // call function
    QString salesAll = storage.GetPurchasesAllMembers();

    //split
    QStringList rows = salesAll.split('\n', Qt::SkipEmptyParts);

    //call populateAllSalesTable
    populateAllSalesTable(rows);
}

void MainWindow::setupAllSalesTable()
{
    //create table
    tableModel = new QStandardItemModel(this);

    //set col and header label
    int colCount = 1;
    tableModel->setColumnCount(colCount);
    tableModel->setHorizontalHeaderLabels({"Search Results"});

    // set model to current tableView
    ui->tableView->setModel(tableModel);

    //adjust to fit
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

void MainWindow::populateAllSalesTable(const QStringList& data)
{
    // Clear prior data
    tableModel->removeRows(0, tableModel->rowCount());

    // Set row count
    int numRows = data.size();

    // Set model size
    tableModel->setRowCount(numRows);

    // Populate the table
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

void MainWindow::on_pushButton_executiveRegular_clicked()
{

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

void MainWindow::on_pushButton_addMember_clicked()
{
    qDebug() << "Add member clicked\n";
    // Create the dialog
    AddMemberDialog dialog;
    //dialog.storage = &storage;

    // Set dialog properties or configure it as needed
    dialog.setWindowTitle("Add New Member");
    dialog.setMinimumSize(300, 200);

    // Create a layout for the dialog
    QVBoxLayout *layout = new QVBoxLayout(&dialog);

    // Add any widgets or elements to the layout
    // ...

    // Show the dialog
    if (dialog.exec() == QDialog::Accepted) {
        QString memberId = dialog.getMemberId();
        QString memberName = dialog.getMemberName();
        QString expirationDate = dialog.getExpirationDate();
        bool isExecutive = dialog.isExecutive();

        qDebug() << "Member ID: " + memberId;
        qDebug() << "Member Name: " + memberName;
        qDebug() << "Expiration Date: " + expirationDate;
        if(isExecutive)
            qDebug() << "Is Executive: true";
        else
            qDebug() << "Is Executive: false";

        QDate date = QDate::fromString(expirationDate, "yyyy-MM-dd");

        // Make sure Id is intiger:
        bool idIsInt = false;
        int id = memberId.toInt(&idIsInt);

        if(!idIsInt)
        {
            QMessageBox::warning(this, "Invalid Member ID", "Please enter a valid integer ID.");
            return;
        }

        // Make sure the id doesn't already exist
        QString existingMemberName = storage.GetMemberNameById(id);
        if(existingMemberName.length() > 0)
        {
            QMessageBox::warning(this, "Invalid Member ID", "Error: That ID already exists.");
            return;
        }

        // Check if the entered date is valid
        if (!date.isValid())
        {
            QMessageBox::warning(this, "Invalid Expiration Date", "Please enter a valid expiration date in the format yyyy-MM-dd.");
            return;
        }

        // make sure the member name is there
        if(memberName.length() == 0)
        {
            QMessageBox::warning(this, "Missing Member Name", "Please enter a Member Name.");
            return;
        }

        Member m(memberName, id, isExecutive,  date, 0, 0, false);

        storage.AddMember(m);

        QMessageBox::information(this, "Success", "New Member Added.");
    }
}

void MainWindow::on_pushButton_deleteMember_clicked()
{
    qDebug() << "Delete member clicked\n";
    // Create the dialog
    DeleteMemberDialog dialog;
    //dialog.storage = &storage;

    // Set dialog properties or configure it as needed
    dialog.setWindowTitle("Delete Member");
    dialog.setMinimumSize(200, 100);

    // Create a layout for the dialog
    QVBoxLayout *layout = new QVBoxLayout(&dialog);

    // Add any widgets or elements to the layout
    // ...

    // Show the dialog
    if (dialog.exec() == QDialog::Accepted) {
        QString memberId = dialog.getMemberId();

        qDebug() << "Member ID: " + memberId;

        // Make sure Id is intiger:
        bool idIsInt = false;
        int id = memberId.toInt(&idIsInt);

        if(!idIsInt)
        {
            QMessageBox::warning(this, "Invalid Member ID", "Please enter a valid integer ID.");
            return;
        }

        // Make sure the id doesn't already exist
        QString existingMemberName = storage.GetMemberNameById(id);
        if(existingMemberName.length() == 0)
        {
            QMessageBox::warning(this, "Error", "Member ID not found.");
            return;
        }

        storage.DeleteMember(id);

        QMessageBox::information(this, "Success", "Member Deleted.");
    }
}

void MainWindow::on_pushButton_addItem_clicked()
{
    qDebug() << "Add Item clicked\n";
    // Create the dialog
    ItemAddDialog dialog;
    //dialog.storage = &storage;

    // Set dialog properties or configure it as needed
    dialog.setWindowTitle("Add Item");
    dialog.setMinimumSize(200, 100);

    // Create a layout for the dialog
    QVBoxLayout *layout = new QVBoxLayout(&dialog);

    // Show the dialog
    if (dialog.exec() == QDialog::Accepted) {
        QString itemName = dialog.getItemName();
        QString priceString = dialog.getPrice();

        qDebug() << "Item Name: " + itemName;

        // make sure the item name is there
        if(itemName.length() == 0)
        {
            QMessageBox::warning(this, "Missing Item Name", "Please enter an Item Name.");
            return;
        }

        // Make sure price is valid:
        bool priceIsDouble = false;
        double price = priceString.toDouble(&priceIsDouble);

        if(!priceIsDouble)
        {
            QMessageBox::warning(this, "Invalid price", "Please enter a valid price.");
            return;
        }

        Item i(itemName, price, 0, false);

        storage.AddItem(i);

        QMessageBox::information(this, "Success", "Item Added.");
    }
}

void MainWindow::on_pushButton_changeItemPrice_clicked()
{
    qDebug() << "Change Item clicked\n";
    // Create the dialog
    ChangeItemPriceDialog dialog;
    //dialog.storage = &storage;

    // Set dialog properties or configure it as needed
    dialog.setWindowTitle("Change Item Price");

    dialog.setMinimumSize(200, 100);

    // Create a layout for the dialog
    QVBoxLayout *layout = new QVBoxLayout(&dialog);

    // Show the dialog
    if (dialog.exec() == QDialog::Accepted) {
        QString itemName = dialog.getItemName();
        QString priceString = dialog.getPrice();

        qDebug() << "Item Name: " + itemName;

        // make sure the item name is there
        if(itemName.length() == 0)
        {
            QMessageBox::warning(this, "Missing Item Name", "Please enter an Item Name.");
            return;
        }

        // Make sure price is valid:
        bool priceIsDouble = false;
        double price = priceString.toDouble(&priceIsDouble);

        if(!priceIsDouble)
        {
            QMessageBox::warning(this, "Invalid price", "Please enter a valid price.");
            return;
        }

        bool found = storage.ChangePrice(itemName, price);

        if(found)
        {
            QMessageBox::information(this, "Success", "Item Price Updated.");
        }
        else
        {
            QMessageBox::warning(this, "Error", "Item Not Found.");
        }
    }
}


void MainWindow::on_pushButton_deleteItem_clicked()
{
    qDebug() << "Delete item clicked\n";
    // Create the dialog
    DeleteItemDialog dialog;
    //dialog.storage = &storage;

    // Set dialog properties or configure it as needed
    dialog.setWindowTitle("Delete Item");
    dialog.setMinimumSize(200, 100);

    // Create a layout for the dialog
    QVBoxLayout *layout = new QVBoxLayout(&dialog);

    // Show the dialog
    if (dialog.exec() == QDialog::Accepted) {
        QString itemName = dialog.getItemName();

        qDebug() << "Delete item named: " + itemName;

        // make sure the item name is there
        if(itemName.length() == 0)
        {
            QMessageBox::warning(this, "Missing Item Name", "Please enter an Item Name.");
            return;
        }

        bool found = storage.DeleteItem(itemName);

        if(found)
        {
            QMessageBox::information(this, "Success", "Item Deleted.");
        }
        else
        {
            QMessageBox::warning(this, "Error", "Item Not Found.");
        }
    }
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

void MainWindow::on_pushButton_itemAddDelete_clicked()
{
    //ADMIN function
}


////////////////////////////////////////////////////////////////////////////////////////
// Regular Member Conversion
// input: none
void MainWindow::on_pushButton_memberConversionRegular_clicked()
{
    //storage.GetConvertToExecutiveRecommendations();
    // call function from datawarehouse
    QString memberConversionRegular = storage.GetConvertToExecutiveRecommendations();

    //split
    QStringList rows = memberConversionRegular.split('\n', Qt::SkipEmptyParts);

    //populate table
    populateMemberConversionRegular(rows);
}

void MainWindow::setupMemberConversionRegular()
{
    //create table
    tableModel = new QStandardItemModel(this);

    //set col and header
    int colCount = 1;
    tableModel->setColumnCount(colCount);
    tableModel->setHorizontalHeaderLabels({"Search Results"});

    //set table view
    ui->tableView->setModel(tableModel);

    //auto adust
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

void MainWindow::populateMemberConversionRegular(const QStringList& data)
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
// Display executive sales report
// input: none

void MainWindow::on_pushButton_salesReportExecutive_clicked()
{
    // getting date
    QDate date = QDate::fromString(ui->lineEdit_salesReportExecutiveDate->text(),"yyyy-MM-dd");

    // Check if the entered date is valid
    if (!date.isValid())
    {
        QMessageBox::warning(this, "Invalid Date", "Please enter a valid date in the format yyyy-MM-dd.");
        return;
    }

    // call datawarehouse function to get sales report for executive members
    QString salesReportEx = storage.GetSalesReportForDate(date, REPORT_EXECUTIVE_ONLY);

    // split the data
    QStringList rows = salesReportEx.split('\n', Qt::SkipEmptyParts);

    //call populate populateExecutiveSalesTable function to display data
    populateExecutiveSalesTable(rows);
}

void MainWindow::setupExecutiveSalesTable()
{
    // create table for model
    tableModel = new QStandardItemModel(this);

    //set column count and header label
    int columnCount = 1;
    tableModel->setColumnCount(columnCount);
    tableModel->setHorizontalHeaderLabels({"Search Results"});

    // set table model to existing tableView
    ui->tableView->setModel(tableModel);

    // Adjust the coumn width to fit stuff
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

void MainWindow::populateExecutiveSalesTable(const QStringList& data)
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
// Display regular sales report
// input: yyyy-MM-dd
void MainWindow::on_pushButton_salesReportRegular_clicked()
{
    //getting date
    QDate date = QDate::fromString(ui->lineEdit_salesReportRegularDate->text(),"yyyy-MM-dd");

    // Check if the entered date is valid
    if (!date.isValid())
    {
        QMessageBox::warning(this, "Invalid Date", "Please enter a valid date in the format yyyy-MM-dd.");
        return;
    }

    // call function from datawarehouse to get sales report for regular memebers
    QString salesReportRg = storage.GetSalesReportForDate(date,REPORT_REGULAR_ONLY);

    //split data
    QStringList rows = salesReportRg.split('\n', Qt::SkipEmptyParts);

    // call populate function to display data on tableView
    populateRegularSalesTable(rows);
}

void MainWindow::setupRegularSalesTable()
{
    //create table for model
    tableModel = new QStandardItemModel(this);

    //set column count and header label
    int colCount = 1;
    tableModel->setColumnCount(colCount);
    tableModel->setHorizontalHeaderLabels({"Search Results"});

    // set table to existing tableView
    ui->tableView->setModel(tableModel);

    // auto adjust column width
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

void MainWindow::populateRegularSalesTable(const QStringList& data)
{
    // clear table
    tableModel->removeRows(0,tableModel->rowCount());

    // set row and column count
    int numRows = data.size();
    int numCols = 1;

    // set row and column count
    tableModel->setRowCount(numRows);
    tableModel->setColumnCount(numCols);

    // populate table
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




