#ifndef ADDMEMBERDIALOG_H
#define ADDMEMBERDIALOG_H

#include "datawarehouse.h"
#include "qcheckbox.h"
#include <QDialog>

class QLabel;
class QLineEdit;
class QPushButton;

class AddMemberDialog : public QDialog {
    Q_OBJECT

public:
    explicit AddMemberDialog(QWidget *parent = nullptr);
    //DataWarehouse* storage;

    QString getMemberId() const;

    QString getMemberName() const;

    QString getExpirationDate() const;

    bool isExecutive();


private:
    QLabel *label;
    QLineEdit *textField;
    QPushButton *okButton;
    QLineEdit *textMemberId;
    QLineEdit *textName;
    QLineEdit *textExpirationDate;
    QCheckBox *checkBoxExecutive;
};

#endif // ADDMEMBERDIALOG_H
