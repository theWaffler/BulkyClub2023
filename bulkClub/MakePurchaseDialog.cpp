#include "MakePurchaseDialog.h"
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "ItemAddDialog.h""
#include "qmessagebox.h"

MakePurchaseDialog::MakePurchaseDialog(QWidget *parent) : QDialog(parent)
{
    this->setWindowTitle("Make new Purchase:");

    // Create the layout for the dialog
    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *labelDate = new QLabel("Date:", this);
    layout->addWidget(labelDate);
    textDate = new QLineEdit(this);
    layout->addWidget(textDate);

    QLabel *labelCustomerID = new QLabel("Member ID:", this);
    layout->addWidget(labelCustomerID);
    textCustomerID = new QLineEdit(this);
    layout->addWidget(textCustomerID);

    QLabel *labelItemName = new QLabel("Item Name:", this);
    layout->addWidget(labelItemName);
    textItemName = new QLineEdit(this);
    layout->addWidget(textItemName);

    QLabel *labelQuantity = new QLabel("Quantity sold:", this);
    layout->addWidget(labelQuantity);
    textQuantity = new QLineEdit(this);
    layout->addWidget(textQuantity);

    QPushButton *okButton = new QPushButton("Make Purchase", this);
    layout->addWidget(okButton);

    // Connect the button's clicked signal to the dialog's accept slot
    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);

    //storage = NULL;
}

QString MakePurchaseDialog::getDate() const
{
    return textDate->text();
}

QString MakePurchaseDialog::getCustomerID() const
{
    return textCustomerID->text();
}

QString MakePurchaseDialog::getItemName() const
{
    return textItemName->text();
}

QString MakePurchaseDialog::getQuantity() const
{
    return textQuantity->text();
}
