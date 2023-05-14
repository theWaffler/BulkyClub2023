#include "datawarehouse.h"

DataWarehouse::DataWarehouse()
{
    LoadMembers();
    LoadTransactions();
}

void DataWarehouse::LoadMembers()
{
    // Todo: populate members collection from "warehouse shoppers.txt"
}

void DataWarehouse::LoadTransactions()
{
    // Todo: populate transactions collection from "day1.txt", "day2.txt", ...
}

QString DataWarehouse::GetSalesReportForDate(QDate date)
{
    // Todo: Write a method to fulfill the following requirement:
    /*
    A store manager should be able to display a sales report for any
    given day. It should include a list of items and quantities sold on that
    day as well names of the members who shopped that day. Display
    the total revenue (including tax) for the given day. It should also
    include number of unique Executive members and Regular
    members who shopped during the given day.
     */
    return NULL; // temporary for stub
}

QString DataWarehouse::GetSalesReportForMembershipType(bool isExecutive)
{
    // Todo: Write a method to fulfill the following requirement:
    /*
    Your team should provide an option to generate the sales report
    (including tax) for any given day by membership type.
     */
    return NULL; // temporary for stub
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
    return NULL; // temporary for stub
}

QString DataWarehouse::GetItemQuantities()
{
    // Todo: Write a method to fulfill the following requirement:
    /*
    A store manager should be able to display the quantity of each item
    sold sorted by item name and the total revenue (without tax) for
    each item.
    */
    return NULL; // temporary for stub
}

QString DataWarehouse::GetExecutiveRebates()
{
    // Todo: Write a method to fulfill the following requirement:
    /*
    A store manager should be able to display the rebate of all the
    Executive members sorted by membership number. Rebates are
    based on purchases before tax.
    */
    return NULL; // temporary for stub
}

QString DataWarehouse::GetMembershipExpirations(QDate month)
{
    // Todo: Write a method to fulfill the following requirement:
    /*
    A store manager should be able to enter a month and obtain a
    display of all members whose memberships expire that month as
    well as the cost to renew their memberships.
    */
    return NULL; // temporary for stub
}

void DataWarehouse::AddMember(Member & m)
{
    // This method is for requirement 7.
    // Todo add m to members collection
}

void DataWarehouse::DeleteMember(int memberId)
{
  // This method is for requirement 7.
  // Todo find member by id and set isDeleted flag in members collection
}

void DataWarehouse::MakePurchase(Transaction* t)
{
    /*
    Your team should provide the capability to create purchases of my
    choice for the new members to validate your software
    */

    CompositeKey key = {t->date, t->customerId, t->productDescription};
    transactions.insert(make_pair(key, t));
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

    return NULL; // temporary for stub
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

    return NULL; // temporary for stub
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
