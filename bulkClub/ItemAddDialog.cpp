#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include "ItemAddDialog.h""
#include "qmessagebox.h"


ItemAddDialog::ItemAddDialog(QWidget *parent) : QDialog(parent)
{
    this->setWindowTitle("Add New Item:");

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



    QPushButton *okButton = new QPushButton("Add Item", this);
    layout->addWidget(okButton);

    // Connect the button's clicked signal to the dialog's accept slot
    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);

    //storage = NULL;
}

QString ItemAddDialog::getItemName() const
{
    return textItemName->text();
}

QString ItemAddDialog::getPrice() const
{
    return textPrice->text();
}


