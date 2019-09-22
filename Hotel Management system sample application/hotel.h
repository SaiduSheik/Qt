#ifndef HOTEL_H
#define HOTEL_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Hotel; }
QT_END_NAMESPACE
class CustomerDialog;

class Hotel : public QMainWindow
{
    Q_OBJECT

public:
    explicit Hotel(QWidget *parent = nullptr);
    ~Hotel();

    Hotel(const Hotel& other) = delete;             // disable copy construction
    Hotel& operator=(const Hotel& other) = delete;  // disable assignment
    Hotel(const Hotel&& other) = delete;
    Hotel& operator=(const Hotel&& other) = delete;

private:
    Ui::Hotel *ui;
    QString m_ImagePath;
    CustomerDialog *dlg;

private slots:
    void browsePhoto();
    void createNewCustomer();
    void clearCustomerDetails();
    void saveCustomerDetails();
    void selectIdProof();
    void openCustomer();
    void searchCustomer(QString&,QString&);
};
#endif // HOTEL_H
