#ifndef MAKEPURCHASEDIALOG_H
#define MAKEPURCHASEDIALOG_H

#include "datawarehouse.h"
#include "qcheckbox.h"
#include <QDialog>

class QLabel;
class QLineEdit;
class QPushButton;

class MakePurchaseDialog : public QDialog {
    Q_OBJECT

public:
    explicit MakePurchaseDialog(QWidget *parent = nullptr);
    //DataWarehouse* storage;

    QString getDate() const;

    QString getCustomerID() const;

    QString getItemName() const;

    QString getQuantity() const;


private:
    QLabel *label;
    QLineEdit *textField;
    QPushButton *okButton;

    QLineEdit *textDate;
    QLineEdit *textCustomerID;
    QLineEdit *textItemName;
    QLineEdit *textQuantity;

};

#endif // MAKEPURCHASEDIALOG_H









