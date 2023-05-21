#include "datawarehouse.h"
#include <map>
#include <set>

struct TransactionDateComparator
{
    bool operator()(const Transaction* transaction, const QDate& date) const
    {
        return transaction->date < date;
    }

    bool operator()(const QDate& date, const Transaction* transaction) const
    {
        return date < transaction->date;
    }
};

DataWarehouse::DataWarehouse()
{
   // qDebug() << "data\n";

    LoadMembers();
    LoadTransactionsAndInventory();
}

void DataWarehouse::LoadMembers()
{
    QFile file(":/members/warehouseShoppers.txt");

    if(!file.exists()){
        qDebug() << "Could not find warehouseShoppers.txt\n";
    }
    if(!file.open(QIODevice::OpenModeFlag::ReadOnly)) {
        qDebug() << "Could not open warehouseShoppers.txt" << "\n";
        return;
    } else {
        QTextStream stream(&file);
        while (!stream.atEnd()) {
            Member newMember;
            QString line = stream.readLine();
            newMember.name = line;
            line = stream.readLine();
            newMember.id = line.toInt();
            line = stream.readLine();
            if (line == "Executive") {
                newMember.isExecutive = true;
            } else {
                newMember.isExecutive = false;
            }
            line = stream.readLine();
            QDate expDate = QDate::fromString(line, "MM/dd/yyyy");
            newMember.expirationDate = expDate;
            Members.push_back(newMember);
        }

        file.close();
    }
}

void DataWarehouse::LoadTransactionsAndInventory()
{

    QString directoryPath = ":/transactions/transactions";
    QDirIterator it(directoryPath, QDir::Files | QDir::NoDotAndDotDot);
    while (it.hasNext()) {
        QString filePath = it.next();
        QFile file(filePath);
        if(!file.exists()){
            qDebug() << "could not find " << filePath << '\n';
        }
        if(!file.open(QIODevice::OpenModeFlag::ReadOnly)) {
            qDebug() << "Could not open " << filePath << "\n";
            return;
        } else {
            QTextStream stream(&file);
            while (!stream.atEnd()) {

                //get all the data
                QString transDateStr = stream.readLine(); //Transaction Date

                //make sure the data is formatted correctly
                QDate transDate = QDate::fromString(transDateStr, "M/d/yyyy");
                if (!transDate.isValid()) {
                    transDate = QDate::fromString(transDateStr, "MM/dd/yy");
                }

                QString id = stream.readLine(); //member id

                QString product = stream.readLine(); //item description

                double price = stream.readLine().toDouble(); //item price

                int quantity = stream.readLine().toInt(); // item quantity

                //updating itemVector
                bool found = false;
                for (Item& item : Inventory) {
                    if (item.product == product) {
                        item.numSold += quantity;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    Item newItem;
                    newItem.product = product;
                    newItem.price = price;
                    newItem.isDeleted = false;
                    newItem.numSold = quantity;
                    Inventory.push_back(newItem);
                }



                //create a new transaction and add the data
                Transaction* newTransaction = new Transaction;
                newTransaction->date = transDate;
                newTransaction->customerId = id.toInt();
                newTransaction->productDescription = product;
                newTransaction->price = price;
                newTransaction->quantity = quantity;

                //Add pointer to transaction to transactionVector
                Transactions.push_back(newTransaction);

            }

            file.close();
        }

    }
  
    sortInventory();
    sortMembers();
}

void DataWarehouse::sortTransactions()
{
    sort(Transactions.begin(), Transactions.end(), [](const Transaction* t1, const Transaction* t2) {
        return t1->date < t2->date;
    });

   // qDebug() << "sorted\n";
}

void DataWarehouse::sortInventory()
{
    sort(Inventory.begin(), Inventory.end(), [](const Item &I1, const Item &I2){
             return I1.product < I2.product;
         });

    // qDebug() << "sorted\n";
}

void DataWarehouse::sortMembers()
{
    sort(Members.begin(), Members.end(), [](const Member &M1, const Member &M2){
        return M1.id < M2.id;
    });

    //qDebug() << "sorted\n";
}

/*void DataWarehouse::sortMembersByName()
{
    sort(Members.begin(), Members.end(), [](const Member &M1, const Member &M2){
        return M1.name < M2.name;
    });
}*/

// Call this for requirements 1 and 2 by including the "reportType" parameter.
// From common.h:
//   #define REPORT_ALL_MEMBERS 0
//   #define REPORT_EXECUTIVE_ONLY 1
//   #define REPORT_REGULAR_ONLY 2
QString DataWarehouse::GetSalesReportForDate(QDate date, int reportType)
{
    // Todo: need to create QString to be output to window
    /*
    A store manager should be able to display a sales report for any
    given day. It should include a list of items and quantities sold on that
    day as well names of the members who shopped that day. Display
    the total revenue (including tax) for the given day. It should also
    include number of unique Executive members and Regular
    members who shopped during the given day.
    */

    QDate targetDate = date;

    map<QString, int> itemQuantities;
    set<int> customerIds;
    bool isExecutive = false; // only used if we have to print report by customer type

    TransactionDateComparator comparator;

    auto range = std::equal_range(Transactions.begin(), Transactions.end(),
                                  targetDate, comparator);

    double totalRevenue = 0;

    for (auto it = range.first; it != range.second; it++)
    {
        Transaction* transaction = *it;

        // add the item name to list of items sold, or increment quantity if it is already there.
        if(itemQuantities.count(transaction->productDescription) > 0)
        {
            itemQuantities[transaction->productDescription] += transaction->quantity;
        }
        else
        {
            itemQuantities[transaction->productDescription] = transaction->quantity;
        }

        // update total daily revenue, with tax of 7.75%
        totalRevenue += transaction->quantity * transaction->price * 1.0775;

        // add the customer to the list of customers for the day
        customerIds.insert(transaction->customerId);

        //qDebug() << transaction->date << "\n";
    }

    // Generate the sales report
    QString report = QString("Daily Sales Report for ");
    report += targetDate.toString();
    switch(reportType)
    {
    case REPORT_ALL_MEMBERS:
        report += ". Membership Type: All.";
        isExecutive = true;
        break;
    case REPORT_EXECUTIVE_ONLY:
        report += ". Membership Type: Executive.";
        break;
    case REPORT_REGULAR_ONLY:
        report += ". Membership Type: Regular.";
        break;
    }

    report += "\n\nItems Sold:\n";

    // Add items sold that day and their quantities
    for (auto it = itemQuantities.begin(); it != itemQuantities.end(); it++)
    {
        report += it->first;
        report += ". Quantity:";
        report += QString::number(it->second);
        report += "\n";
    }

    // Add total revenue
    report += "\nTotal Daily Revenue (including tax): ";
    report += QString::number(totalRevenue);

    // Add details on members who shopped that day
    int totalExecutive = 0;
    int totalRegular = 0;
    report += "\n\nCustomers: \n";
    for (auto it = customerIds.begin(); it != customerIds.end(); it++)
    {
        int customerId = *it;

        // find the customer info
        bool found = false;
        for (auto it2 = Members.begin(); it2 != Members.end(); ++it2)
        {
            Member customer = *it2;
            //qDebug() << "\nLookup (from custIds): " << customerId;
            //qDebug() << "Match (from members): " << customer.id;
            //qDebug() << "Inequality: " << (customer.id == customerId);
            if(customer.id == customerId)
            {
                found = true;
                //qDebug() << "\nFound it.\n";
                if(reportType == REPORT_ALL_MEMBERS || customer.isExecutive == isExecutive)
                {
                    report += customer.name;
                    report += "\n";

                    if(customer.isExecutive)
                    {
                        totalExecutive++;
                    }
                    else
                    {
                        totalRegular++;
                    }
                }

                break; // we found the customer we are looking for. no need to continue.
            }
        }

        if(!found)
        {
            report += "Error: Customer not found.\n";
            //qDebug() << "Error Id not found";
        }
    }

    // Add count of unique members (executive and regular)
    if(reportType == REPORT_ALL_MEMBERS || reportType == REPORT_EXECUTIVE_ONLY)
    {
        report += "\nTotal Executive members: ";
        report += QString::number(totalExecutive);
    }
    if(reportType == REPORT_ALL_MEMBERS || reportType == REPORT_REGULAR_ONLY)
    {
        report += "\nTotal Regular members: ";
        report += QString::number(totalRegular);
    }

    return report;
}

// Call this for requirement 3
QString DataWarehouse::GetPurchasesAllMembers()
{
    /*
    A store manager should be able to display the total purchases for
    each member including tax sorted by membership number. The
    display should also include a grand total including tax of all the
    purchases for all the members.
    */

    QString report = QString("Sales by Member: \n");
    double totalRevenue = 0;

    for (auto it = Members.begin(); it != Members.end(); it++)
    {
        double customerTotal = 0;
        Member customer = *it;

        report += "\n\nCustomer ID: " +  QString::number(customer.id) + ", Name: " + customer.name;

        for (auto it = Transactions.begin(); it != Transactions.end(); it++)
        {
            Transaction* transaction = *it;
            if(transaction->customerId != customer.id)
            {
                continue;
            }

            customerTotal += transaction->price * transaction->quantity;

            report += "\nItem: " + transaction->productDescription
                    + " Quantity: " + QString::number(transaction->quantity)
                    + " Price: " + QString::number(transaction->price);
        }

        totalRevenue += customerTotal;

        report += "\nTotal Purchases (including tax): " + QString::number(customerTotal * 1.0775);
    }

    report += "\n\nGrand Total (including tax): " + QString::number(totalRevenue * 1.0775);

    return report;
}

// Call this for requirement 4
QString DataWarehouse::GetItemQuantities()
{
    /*
    A store manager should be able to display the quantity of each item
    sold sorted by item name and the total revenue (without tax) for
    each item.
    */

    map<QString, tuple<int, double>> itemQuantities;

    for (auto it = Transactions.begin(); it != Transactions.end(); it++)
    {
        Transaction* transaction = *it;

        // add the item name to list of items sold, or increment quantity if it is already there.
        if(itemQuantities.count(transaction->productDescription) > 0)
        {
            auto tuple = itemQuantities[transaction->productDescription];
            int quantity = get<0>(tuple);
            double price = get<1>(tuple);
            itemQuantities[transaction->productDescription] =
                make_tuple(quantity + transaction->quantity, price + transaction->price * transaction->quantity);

        }
        else
        {
            itemQuantities.insert(make_pair(transaction->productDescription,
                                                 make_tuple(transaction->quantity,
                                                            transaction->price * transaction->quantity)));
        }
    }

    QString report = QString("Quantity of Items Sold: \n");

    for (auto it = itemQuantities.begin(); it != itemQuantities.end(); it++)
    {
        report += "\nItem: " + it->first + ". Quantity: "
                  + QString::number(get<0>(it->second)) + " Total Revenue (without tax): "
                  + QString::number(get<1>(it->second));
    }

    return report;
}

// Call this for requirement 10
QString DataWarehouse::GetItemQuantity(QString itemName)
{
    /*
    A store manager should be able to enter an item name and only
    display the quantity of that item sold as well as the total revenue
    (without tax) for the item. No other items should be displayed.
    */

    int quantity = 0;
    double revenue = 0;

    QString report = QString("Quantity of " + itemName + " Sold: ");

    for (auto it = Transactions.begin(); it != Transactions.end(); it++)
    {
        Transaction* transaction = *it;

        if(transaction->productDescription == itemName)
        {
            revenue += transaction->quantity * transaction->price;
            quantity += transaction->quantity;
        }
    }

    report += QString::number(quantity) + ", Total Revenue (without tax): " + QString::number(revenue);

    return report;
}

// Call this for requirement 5
QString DataWarehouse::GetExecutiveRebates()
{
    /*
    A store manager should be able to display the rebate of all the
    Executive members sorted by membership number. Rebates are
    based on purchases before tax.
    */

    QString report = QString("Executive Member Rebates: \n");

    for (auto it = Members.begin(); it != Members.end(); it++)
    {
        auto customer = *it;
        if(!customer.isExecutive)
        {
            continue;
        }

        report += customer.name + ": " + QString::number(GetMemberRebate(customer.id)) +"\n";
    }

    return report;
}

// Call this for requirement 12
QString DataWarehouse::GetConvertToExecutiveRecommendations()
{
    int total = 0;
    QString report = QString("Regular Members who should convert to Executive: \n");

    // todo: sort

    for (auto it = Members.begin(); it != Members.end(); it++)
    {
        auto customer = *it;
        if(customer.isExecutive)
        {
            continue;
        }

        if(ShouldBeExecutive(customer.id) && !customer.isDeleted)
        {
            report += customer.name + ", ID:" + QString::number(customer.id) + "\n";
            total++;
        }
    }

    report += "\nTotal" + QString::number(total);

    return report;
}

// Call this for requirement 13
QString DataWarehouse::GetConvertToRegularRecommendations()
{
    int total = 0;
    QString report = QString("Executive Members who should convert to Regular: \n");

    // todo: sort

    for (auto it = Members.begin(); it != Members.end(); it++)
    {
        auto customer = *it;
        if(!customer.isExecutive)
        {
            continue;
        }

        if(!ShouldBeExecutive(customer.id) && !customer.isDeleted)
        {
            report += customer.name + ", ID:" + QString::number(customer.id) + "\n";
            total++;
        }
    }

    report += "\nTotal: " + QString::number(total);

    return report;
}

bool DataWarehouse::ShouldBeExecutive (int memberId)
{
    double priceDifference = 120 - 65; // exec membership is $120, regular is $65
    if (GetMemberRebate(memberId) > priceDifference)
    {
        return true;
    }
    return false;
}

double DataWarehouse::GetMemberRebate(int memberId)
{
    double totalAmountSpent = 0;

    for (auto it = Members.begin(); it != Members.end(); it++)
    {
        auto customer = *it;

        if(customer.id != memberId)
        {
            continue;
        }

        for (auto it = Transactions.begin(); it != Transactions.end(); it++)
        {
            Transaction* transaction = *it;
            if(transaction->customerId != customer.id)
            {
                continue;
            }

            totalAmountSpent += transaction->quantity * transaction->price;
        }
    }

    return totalAmountSpent * 0.02;
}

// Call this for requirement 6
QString DataWarehouse::GetMembershipExpirations(int month, int year)
{
    /*
    A store manager should be able to enter a month and obtain a
    display of all members whose memberships expire that month as
    well as the cost to renew their memberships.
    */

    QString report = QString("Memberships expiring in " + QString::number(month) +"/" + QString::number(year) + ":\n");

    for (auto it = Members.begin(); it != Members.end(); it++)
    {
        auto customer = *it;

        if(customer.expirationDate.month() == month && customer.expirationDate.year() == year)
        {
            QString renewalCost = customer.isExecutive ? "$120" : "$65";
            report += customer.name + ", Renewal cost: " + renewalCost +"\n";
        }
    }

    return report;
}

// Call for requrement 7
void DataWarehouse::AddMember(Member m)
{
    Members.push_back(m);
    sortMembers();
}

// Call for requirement 7
void DataWarehouse::DeleteMember(int memberId)
{
    for (auto it = Members.begin(); it != Members.end(); ++it)
    {
        auto member = *it;
        if(member.id == memberId)
        {
            member.isDeleted = true;
            return;
        }
    }
}

// Call for requiremet 8.
QString DataWarehouse::MakePurchase(Transaction* t)
{
    // Make sure customer is found and not deleted.
    bool found = false;
    for (auto it = Members.begin(); it != Members.end(); it++)
    {
        auto member = *it;
        if(member.id == t->customerId)
        {
            found = true;
            if(member.isDeleted)
            {
                return QString("Error, customer " + member.name + " is deleted.");
            }
        }
    }

    if(!found)
    {
        return QString("Error, customer not found.");
    }

    found = false;
    // Make sure item is found and not deleted.
    for (auto it = Inventory.begin(); it != Inventory.end(); it++)
    {
        auto item = *it;

        if(item.product == t->productDescription)
        {
            found = true;
            if(item.isDeleted)
            {
                return QString("Error, item " + item.product + " is deleted.");
            }
        }
    }

    if(!found)
    {
        return QString("Error, item not found.");
    }

    Transactions.push_back(t);
    sortTransactions();

    return QString("Purchase added.");
}

// Call fore requrirement 9
void DataWarehouse::AddItem(Item i)
{
    Inventory.push_back(i);
    sortInventory();
}

// Call for requirement 9
void DataWarehouse::DeleteItem(QString itemName)
{
    for (auto it = Inventory.begin(); it != Inventory.end(); it++)
    {
        auto item = *it;

        if(item.product == itemName)
        {
            item.isDeleted = true;
            return;
        }
    }
}

// Call for requirement 9
void DataWarehouse::ChangePrice(QString itemName, double price)
{
    for (auto it = Inventory.begin(); it != Inventory.end(); it++)
    {
        auto item = *it;

        if(item.product == itemName)
        {
            item.price = price;
            return;
        }
    }
}

// Call for requirement 11. If name is given instead of id,
// call this to get the Id, then call GetMemberPurchases(id);
int DataWarehouse::GetMemberIdByName(QString memberName)
{
    for (auto it = Members.begin(); it != Members.end(); it++)
    {
        auto customer = *it;

        if(customer.name == memberName)
        {
            return customer.id;
        }
    }

    return -1; // customer not found
}

// Call for requirement 11
QString DataWarehouse::GetMemberPurchases(int memberId)
{
    /*
    A store manager should be able to enter a membership number or
    name and display the total purchases including tax for that member.
    */

    double customerTotal = 0;
    bool found = false;

    QString name;

    for (auto it = Members.begin(); it != Members.end(); it++)
    {
        auto member = *it;
        if(member.id == memberId)
        {
            found = true;
            name = member.name;
        }
    }

    if(!found)
    {
        return "Error: Member not found.";
    }

    QString report = QString("Sales for" + name + ":");

    for (auto it = Transactions.begin(); it != Transactions.end(); it++)
    {
        Transaction* transaction = *it;
        if(transaction->customerId != memberId)
        {
            continue;
        }

        customerTotal += transaction->price * transaction->quantity;

        report += "\nItem: " + transaction->productDescription
                  + " Quantity: " + QString::number(transaction->quantity)
                  + " Price: " + QString::number(transaction->price);
    }

    return "\nTotal Purchases (including tax): " + QString::number(customerTotal * 1.0775);
}
