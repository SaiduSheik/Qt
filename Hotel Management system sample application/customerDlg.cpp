#include "customerDlg.h"
#include "ui_customerDlg.h"
#include "constants.h"

#include <QMessageBox>
#include <QPrinter>
#include <QPainter>
#include<QTextDocument>

/*****************CustomerDialog************************
 ******************Constructor************************
 * @param parent QWidget
 * @return none
 ****************************************************/
CustomerDialog::CustomerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    ui->treeWidget->setColumnCount(COL_COUNT);

    connect(ui->searchButton,&QPushButton::clicked,this,&CustomerDialog::searchCustomer);
    connect(ui->billButton,&QPushButton::clicked,this,&CustomerDialog::calculateBill);
}

/*****************CustomerDialog************************
 ******************Destructor************************
 * @param none
 * @return none
 ****************************************************/
CustomerDialog::~CustomerDialog()
{
    delete ui;
}

/*****************CustomerDialog************************
 ******************searchCustomer************************
 * @param none
 * @return none
 ****************************************************/
void CustomerDialog::searchCustomer()
{
    QString number = ui->numerEdit->text();
    QString name = ui->nameEdit->text();
    if(name.isEmpty()|| number.isEmpty())
    {
        QMessageBox::warning(this,WARNING,WARNING_MSG);
    }
    ui->treeWidget->clear();
    emit searchSignal(name,number);
}
/*****************CustomerDialog************************
 ******************showCustomerDetails************************
 * @param customerDetails
 * @return none
 ****************************************************/
void CustomerDialog::showCustomerDetails(const QString &customerDetails)
{
    if(customerDetails.isEmpty())
    {
        QMessageBox::information(this,INFO,NO_RECORDS);
    }

    QStringList strlstDetails = customerDetails.split(DELIMITER);
    if(strlstDetails.size() >= COL_COUNT)
    {
        QTreeWidgetItem *treeItem = new QTreeWidgetItem(ui->treeWidget);
        for(int i=0;i<COL_COUNT;i++)
        {
            treeItem->setText(i,strlstDetails.at(i));
        }
    }
}

/*****************CustomerDialog************************
 ******************calculateBill************************
 * @param none
 * calculates the total bill for the customer
 * and genarates customername_Bill.pdf
 * and print the bill
 * @return none
 ****************************************************/
void CustomerDialog::calculateBill()
{
    QTreeWidgetItem *custItem = ui->treeWidget->currentItem();
    if(nullptr !=custItem )
    {
        QString html =
                QString("<html>\
                        <div align=right>\
                city\
                </div>\
                <div align=left>\
                Sender Name<br>\
                street 34/56A<br>\
                121-43 city\
                </div>\
                <head>\
                <style>\
                table, th, td {\
                            border: 1px solid black;\
                            border-collapse: collapse;\
                        }\
                        th, td {\
                            padding: 5px;\
                            text-align: left;\
                        }\
                        </style>\
                        </head>\
                        <body>\
                        <h1 align=center>HOTEL NAME</h1>\
                <table style=\"width:100%\">\
                <tr>\
                <th>CustomerName</th>\
                <th>Address</th> \
                <th>Days</th>\
                <th>Amount</th>\
                </tr>\
                <tr>\
                <td>%1</td>\
                <td>%2</td>\
                <td>%3</td>\
                <td>%4</td>\
                </tr> \
                </table>\
                <p>payment term-Cash/Check </p>\
                <p>casher name </p>\
                <p align=right>signature: </p>\
                <p>casher signature of the guest: </p>\
                </body>\
                </html>").arg(custItem->text(0)).arg(custItem->text(2)).arg(custItem->text(3)).arg(QString::number( custItem->text(3).toInt()*500));
                QTextDocument document;
                document.setHtml(html);

        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setPaperSize(QPrinter::A4);
        QString pdfFileName = QString("%1_Bill.pdf").arg(custItem->text(0));
        printer.setOutputFileName(pdfFileName);
        printer.setPageMargins(QMarginsF(15, 15, 15, 15));
        document.print(&printer);
        QMessageBox::information(this,INFO,SUCCESS);
    }
    else
    {
        QMessageBox::information(this,INFO,SELECT_RECORD);
    }
}

