#ifndef ITEMADDDIALOG_H
#define ITEMADDDIALOG_H

#include "datawarehouse.h"
#include "qcheckbox.h"
#include <QDialog>

class QLabel;
class QLineEdit;
class QPushButton;

class ItemAddDialog : public QDialog {
    Q_OBJECT

public:
    explicit ItemAddDialog(QWidget *parent = nullptr);
    //DataWarehouse* storage;

    QString getItemName() const;

    QString getPrice() const;


private:
    QLabel *label;
    QLineEdit *textField;
    QPushButton *okButton;
    QLineEdit *textItemName;
    QLineEdit *textPrice;

};

#endif // ITEMADDDIALOG_H
