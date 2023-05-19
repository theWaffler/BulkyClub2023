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
    qDebug() << "data\n";

    // start of temp code for testing until LoadTransactions is implemented
    Transaction* t = new Transaction(QDate(2011,1,1), 1, "hello", 1, 1);
    transactions.push_back(t);
    t = new Transaction(QDate(2012,1,1), 1, "hello", 1, 1);
    transactions.push_back(t);
    t = new Transaction(QDate(2011,1,1), 1, "whatsup", 1, 1);
    transactions.push_back(t);
    t = new Transaction(QDate(2009,1,1), 1, "hello", 1, 1);
    transactions.push_back(t);
    // end of temp code for testing until LoadTransactions is implemented

    LoadMembers();
    LoadTransactions();
    //LoadInventory(); // todo: uncomment once this method is implemented.

    sortData();
}

void DataWarehouse::LoadMembers()
{
    // Todo: populate members collection from "warehouse shoppers.txt"
}

void DataWarehouse::LoadTransactions()
{
    // Todo: populate transactions collection from "day1.txt", "day2.txt", ...
}

void DataWarehouse::sortData()
{
    sort(transactions.begin(), transactions.end(), [](const Transaction* t1, const Transaction* t2) {
        return t1->date < t2->date;
    });

    for(auto* i : transactions)
    {
        qDebug() << i->date << "\n";
    }

    qDebug() << "sorted\n";
}


// Note: this method satisfies requirements 1 and 2 by including the "reportType" parameter.
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

    auto range = std::equal_range(transactions.begin(), transactions.end(),
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

        qDebug() << transaction->date << "\n";
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
        for (auto it = Members.begin(); it != Members.end(); ++it)
        {
            auto customer = *it;
            if(customer.id == customerId)
            {
                found = true;
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
            if(!found)
            {
                report += "Error: Customer not found.\n";
            }
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

QString DataWarehouse::GetAllPurchases()
{
    // Todo: Write a method to fulfill the following requirement:
    /*
    A store manager should be able to display the total purchases for
    each member including tax sorted by membership number. The
    display should also include a grand total including tax of all the
    purchases for all the members.
     */
    return "Not done yet..."; // temporary for stub
}

QString DataWarehouse::GetItemQuantities()
{
    // Todo: Write a method to fulfill the following requirement:
    /*
    A store manager should be able to display the quantity of each item
    sold sorted by item name and the total revenue (without tax) for
    each item.
    */
    return "Not done yet..."; // temporary for stub
}

QString DataWarehouse::GetExecutiveRebates()
{
    // Todo: Write a method to fulfill the following requirement:
    /*
    A store manager should be able to display the rebate of all the
    Executive members sorted by membership number. Rebates are
    based on purchases before tax.
    */
    return "Not done yet..."; // temporary for stub
}

QString DataWarehouse::GetMembershipExpirations(QDate month)
{
    // Todo: Write a method to fulfill the following requirement:
    /*
    A store manager should be able to enter a month and obtain a
    display of all members whose memberships expire that month as
    well as the cost to renew their memberships.
    */
    return "Not done yet..."; // temporary for stub
}

void DataWarehouse::AddMember(Member* m)
{
    // todo: not sure if Members will use pointers
//Members.push_back(m);
}

void DataWarehouse::DeleteMember(int memberId)
{
  // This method is for requirement 7.
  // Todo find member by id and set isDeleted flag in members collection
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

void DataWarehouse::MakePurchase(Transaction* t)
{
    transactions.push_back(t);
    sortData();
}

void DataWarehouse::AddItem(Item i)
{
    // This method is for requirement 9.
    // Todo insert i into items collection
}

void DataWarehouse::DeleteItem(int itemId)
{
    // This method is for requirement 9.
    // Todo find item in items by id, and remove it from collection.
}

void DataWarehouse::ChangePrice(int itemId)
{
    // This method is for requirement 9.
   // Todo find item in items by id, and update its price.
}

QString DataWarehouse::GetSalesInfoForItem(QString itemName)
{
    /*
    A store manager should be able to enter an item name and only
    display the quantity of that item sold as well as the total revenue
    (without tax) for the item. No other items should be displayed.
    */

    // todo: find transactions for the specified item and calculate totals

    return "Not done yet..."; // temporary for stub
}

int DataWarehouse::GetMemberIdByName(QString memberName)
{
    // this is part of requirement 11. If name is given instead of id,
    // call this to get the Id, then call GetTotalPurchases(id);
    return 0; // temporary for stub
}

QString DataWarehouse::GetTotalPurchases(int memberId)
{
    /*
    A store manager should be able to enter a membership number or
    name and display the total purchases including tax for that member.
    */

    // todo: find transactions for the specified member and calculate totals
    // note, if member name is provided, we need to call GetMemberIdByName
    // first, then call this

    return "Not done yet..."; // temporary for stub
}

bool DataWarehouse::ShouldBeExecutive (int memberId)
{
    /*
    Your program should be able to determine if any Regular customer
    should convert their membership to Executive status using the given
    sales data. Display the number of recommended conversions.
    */
    // Todo: find transactions for the customer and do calculations.
    // NOTE: we will also need a function to display the number of recommended conversions.
    return false; // temporary for stub
}

bool DataWarehouse::ShouldBeRegularMember(int memberId)
{
    // Note, this is for requirement 13. Once ShouldBeExecutive works, this
    // should work. as with that method, we will also need one to display totals.
    return !ShouldBeExecutive(memberId);
}
