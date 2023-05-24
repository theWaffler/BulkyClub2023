#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include "AddMemberDialog.h"
#include "qmessagebox.h"


    AddMemberDialog::AddMemberDialog(QWidget *parent) : QDialog(parent)
    {
        this->setWindowTitle("Add New Member:");

        // Create the layout for the dialog
        QVBoxLayout *layout = new QVBoxLayout(this);

        QLabel *labelMemberId = new QLabel("Member ID:", this);
        layout->addWidget(labelMemberId);
        textMemberId = new QLineEdit(this);
        layout->addWidget(textMemberId);

        QLabel *labelMemberName = new QLabel("Member Name:", this);
        layout->addWidget(labelMemberName);
        textName = new QLineEdit(this);
        layout->addWidget(textName);

        QLabel *labelExpirationDate = new QLabel("Expiration Date:", this);
        layout->addWidget(labelExpirationDate);
        textExpirationDate = new QLineEdit(this);
        layout->addWidget(textExpirationDate);

        checkBoxExecutive = new QCheckBox("Is Executive", this);
        layout->addWidget(checkBoxExecutive);

        QPushButton *okButton = new QPushButton("Add Member", this);
        layout->addWidget(okButton);

        // Connect the button's clicked signal to the dialog's accept slot
        connect(okButton, &QPushButton::clicked, this, &QDialog::accept);

        //storage = NULL;
    }

    QString AddMemberDialog::getMemberId() const {
        return textMemberId->text();
    }

    QString AddMemberDialog::getMemberName() const {
        return textName->text();
    }

    QString AddMemberDialog::getExpirationDate() const {
        return textExpirationDate->text();
    }

    bool AddMemberDialog::isExecutive() {
        return checkBoxExecutive->isChecked();
    }

