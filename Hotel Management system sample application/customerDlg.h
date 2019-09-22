#ifndef CUSTOMERDLG_H
#define CUSTOMERDLG_H


#include <QDialog>

namespace Ui {
class Dialog;
}

class CustomerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CustomerDialog(QWidget *parent = nullptr);
    ~CustomerDialog();

    CustomerDialog(const CustomerDialog& other) = delete;             // disable copy construction
    CustomerDialog& operator=(const CustomerDialog& other) = delete;  // disable assignment

    CustomerDialog(const CustomerDialog&& other) = delete;
    CustomerDialog& operator=(const CustomerDialog&& other) = delete;

    void showCustomerDetails(const QString &);

private:
    Ui::Dialog *ui;

signals:
    void searchSignal(QString&,QString&);

private slots:
    void searchCustomer();
    void calculateBill();
};

#endif // CUSTOMERDLG_H
