#ifndef MEMBERSEARCH_H
#define MEMBERSEARCH_H

#include <QWidget>
#include <QLine>
#include <QPushButton>
#include <QLineEdit>

namespace Ui {
class memberSearch;
}

class memberSearch : public QWidget
{
    Q_OBJECT

public:
    explicit memberSearch(QWidget *parent = nullptr);
    ~memberSearch();

signals:
    void searchRequested(const QString& memberName, const QString& memberNumber);

private slots:
    void on_pushButton_memberSearchButton_clicked();

private:
    Ui::memberSearch *ui;
    QLineEdit* lineEdit_memberNumberSearch;
};

#endif // MEMBERSEARCH_H
