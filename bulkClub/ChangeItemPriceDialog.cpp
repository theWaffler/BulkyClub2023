#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include "ChangeItemPriceDialog.h"""
#include "qmessagebox.h"


ChangeItemPriceDialog::ChangeItemPriceDialog(QWidget *parent) : QDialog(parent)
{
    this->setWindowTitle("Change Item Price:");

    // Create the layout for the dialog
    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *labelItemName = new QLabel("Item Name:", this);
    layout->addWidget(labelItemName);
    textItemName = new QLineEdit(this);
    layout->addWidget(textItemName);

    QLabel *labelPrice = new QLabel("Set Price:", this);
    layout->addWidget(labelPrice);
    textPrice = new QLineEdit(this);
    layout->addWidget(textPrice);



    QPushButton *okButton = new QPushButton("Update Item", this);
    layout->addWidget(okButton);

    // Connect the button's clicked signal to the dialog's accept slot
    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);

    //storage = NULL;
}

QString ChangeItemPriceDialog::getItemName() const
{
    return textItemName->text();
}

QString ChangeItemPriceDialog::getPrice() const
{
    return textPrice->text();
}


