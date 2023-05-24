#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "DeleteMemberDialog.h"
#include "qmessagebox.h"


DeleteMemberDialog::DeleteMemberDialog(QWidget *parent) : QDialog(parent)
{
    this->setWindowTitle("Delete Member:");

    // Create the layout for the dialog
    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *labelMemberId = new QLabel("Member ID:", this);
    layout->addWidget(labelMemberId);
    textMemberId = new QLineEdit(this);
    layout->addWidget(textMemberId);

    QPushButton *okButton = new QPushButton("Delete Member", this);
    layout->addWidget(okButton);

    // Connect the button's clicked signal to the dialog's accept slot
    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);

    //storage = NULL;
}

QString DeleteMemberDialog::getMemberId() const {
    return textMemberId->text();
}


