#ifndef DELETEITEMDIALOG_H
#define DELETEITEMDIALOG_H

#include "datawarehouse.h"
#include "qcheckbox.h"
#include <QDialog>

class QLabel;
class QLineEdit;
class QPushButton;

class DeleteItemDialog : public QDialog {
    Q_OBJECT

public:
    explicit DeleteItemDialog(QWidget *parent = nullptr);
    QString getItemName() const;

private:
    QLabel *label;
    QLineEdit *textField;
    QPushButton *okButton;
    QLineEdit *textMemberId;
    QLineEdit *textName;
    QLineEdit *textExpirationDate;
    QCheckBox *checkBoxExecutive;
};

#endif // DELETEITEMDIALOG_H
