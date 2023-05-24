#ifndef CHANGEITEMPRICEDIALOG_H
#define CHANGEITEMPRICEDIALOG_H

#include "datawarehouse.h"
#include "qcheckbox.h"
#include <QDialog>

class QLabel;
class QLineEdit;
class QPushButton;

class ChangeItemPriceDialog : public QDialog {
    Q_OBJECT

public:
    explicit ChangeItemPriceDialog(QWidget *parent = nullptr);
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

#endif // CHANGEITEMPRICEDIALOG_H
