

#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "DeleteItemDialog.h"
#include "qmessagebox.h"


DeleteItemDialog::DeleteItemDialog(QWidget *parent) : QDialog(parent)
{
    this->setWindowTitle("Delete Item:");

    // Create the layout for the dialog
    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *labelMemberId = new QLabel("Item Name:", this);
    layout->addWidget(labelMemberId);
    textMemberId = new QLineEdit(this);
    layout->addWidget(textMemberId);

    QPushButton *okButton = new QPushButton("Delete Item", this);
    layout->addWidget(okButton);

    // Connect the button's clicked signal to the dialog's accept slot
    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);

    //storage = NULL;
}

QString DeleteItemDialog::getItemName() const {
    return textMemberId->text();
}

