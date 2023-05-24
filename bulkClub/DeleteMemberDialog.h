#ifndef DELETEMEMBERDIALOG_H
#define DELETEMEMBERDIALOG_H

#include "datawarehouse.h"
#include "qcheckbox.h"
#include <QDialog>

class QLabel;
class QLineEdit;
class QPushButton;

class DeleteMemberDialog : public QDialog {
    Q_OBJECT

public:
    explicit DeleteMemberDialog(QWidget *parent = nullptr);
    QString getMemberId() const;

private:
    QLabel *label;
    QLineEdit *textField;
    QPushButton *okButton;
    QLineEdit *textMemberId;
    QLineEdit *textName;
    QLineEdit *textExpirationDate;
    QCheckBox *checkBoxExecutive;
};

#endif // DELETEMEMBERDIALOG_H
