#include "hotel.h"
#include "ui_hotel.h"
#include "ui_customerDlg.h"
#include "customerDlg.h"
#include "constants.h"

#include <QFileDialog>
#include <QTextStream>
#include<QDebug>
#include <QMessageBox>
#include <QDomDocument>

/******************Hotel************************
 ******************Constructor************************
 * @param parent QWidget
 * @return none
 ****************************************************/
Hotel::Hotel(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Hotel)
{
    ui->setupUi(this);
    ui->CustomerDetails_GrpBox->hide();

    connect(ui->photoLabel,       &ClickableLabel::clicked, this,   &Hotel::browsePhoto);
    connect(ui->actionNew,        &QAction::triggered,      this,   &Hotel::createNewCustomer);
    connect(ui->clearButton,      &QPushButton::clicked,    this,   &Hotel::clearCustomerDetails);
    connect(ui->submitButton,     &QPushButton::clicked,    this,   &Hotel::saveCustomerDetails);
    connect(ui->idProofToolButton,&QToolButton::clicked,    this,   &Hotel::selectIdProof);
    connect(ui->actionOpen,       &QAction::triggered,      this,   &Hotel::openCustomer);
}

/******************Hotel************************
 ******************Destructor************************
 * @param none
 * @return none
 ****************************************************/
Hotel::~Hotel()
{
    delete ui;
}

/******************Hotel************************
 ******************browsePhoto************************
 * @param none
 * By promoting QLabel to clickableLabel(clickablelabel.h),
 * handling click signal on QLabel
 * @return none
 ****************************************************/
void Hotel::browsePhoto()
{
    QString fileName = QFileDialog::getOpenFileName(this,CAPTION, DIR, FILTER);
    if(!fileName.isEmpty() && m_ImagePath != fileName)
    {
        ui->photoLabel->setScaledContents(true);
        ui->photoLabel->setPixmap(QPixmap(fileName).scaled(ui->photoLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        m_ImagePath = fileName;
    }
}

/******************Hotel****************************
 ******************createNewCustomer************************
 * @param none
 * Handling New action
 * @return none
 ****************************************************/
void Hotel::createNewCustomer()
{
    clearCustomerDetails();
    ui->CustomerDetails_GrpBox->show();
}

/******************Hotel****************************
 ******************clearCustomerDetails************************
 * @param none
 * resetting UI with default values
 * @return none
 ****************************************************/
void Hotel::clearCustomerDetails()
{
    ui->customerNameEdit->clear();
    ui->customerAddressEdit->clear();
    ui->numOfDaysspinBox->clear();
    ui->typeOfRoomcomboBox->setCurrentText("");
    ui->idProofLabel->setText("");
    ui->photoLabel->setText(PHOTO);
    ui->phNumEdit->clear();
}

/******************Hotel****************************
 ******************saveCustomerDetails************************
 * @param none
 * To save customer details in .xml file
 * @return none
 ****************************************************/
void Hotel::saveCustomerDetails()
{
    if(ui->customerNameEdit->text().isEmpty() || ui->phNumEdit->text().isEmpty())
    {
        QMessageBox::warning(this,WARNING,WARNING_MSG);
        return;
    }

    QDomDocument xml;
    QDomElement rootText;

    QFile file("CustomerDetails.xml");

    if(file.open(QIODevice::ReadOnly) && xml.setContent(&file))
    {
        if(xml.elementsByTagName(TAG_CUSTOMER_DETAILS).size() > 0)
        {
            rootText = xml.elementsByTagName(TAG_CUSTOMER_DETAILS).at(0).toElement();
        }
    }
    else
    {
        rootText = xml.createElement(TAG_CUSTOMER_DETAILS);
    }
    file.close();
    xml.appendChild(rootText);
    if (file.open(QIODevice::WriteOnly| QIODevice::Text | QIODevice::Truncate))
    {
        QDomElement custEle = xml.createElement(TAG_CUSTOMER);
        rootText.appendChild(custEle);

        QDomElement root = xml.createElement(TAG_UID);
        root.setAttribute(TAG_PHONE,ui->phNumEdit->text());
        root.setAttribute(TAG_NAME,ui->customerNameEdit->text());
        custEle.appendChild(root);

        QDomElement tagName = xml.createElement(TAG_NAME);
        root.appendChild(tagName);
        QDomText textName = xml.createTextNode(ui->customerNameEdit->text()+DELIMITER);
        tagName.appendChild(textName);

        QDomElement tagPhone = xml.createElement(TAG_PHONE);
        root.appendChild(tagPhone);
        QDomText textPhone = xml.createTextNode((ui->phNumEdit->text() + DELIMITER));
        tagPhone.appendChild(textPhone);

        QDomElement tagAddress = xml.createElement(TAG_ADDRESS);
        root.appendChild(tagAddress);
        QDomText textAddress = xml.createTextNode(ui->customerAddressEdit->text()+DELIMITER);
        tagAddress.appendChild(textAddress);

        QDomElement tagDays = xml.createElement(TAG_DAYS);
        root.appendChild(tagDays);
        QDomText textDays = xml.createTextNode(ui->numOfDaysspinBox->text()+DELIMITER);
        tagDays.appendChild(textDays);

        QDomElement tagRoomType = xml.createElement(TAG_ROOM_TYPE);
        root.appendChild(tagRoomType);
        QDomText textRoomType = xml.createTextNode(ui->typeOfRoomcomboBox->currentText()+DELIMITER);
        tagRoomType.appendChild(textRoomType);

        QDomElement tagId = xml.createElement(TAG_ID);
        root.appendChild(tagId);
        QDomText textId = xml.createTextNode(ui->idProofLabel->text()+DELIMITER);
        tagId.appendChild(textId);

        QDomElement tagPhoto = xml.createElement(PHOTO);
        root.appendChild(tagPhoto);
        QDomText textPhoto = xml.createTextNode(m_ImagePath+DELIMITER);
        tagPhoto.appendChild(textPhoto);

        QDomElement tagStatus = xml.createElement(TAG_STATUS);
        root.appendChild(tagStatus);
        QDomText textStatus = xml.createTextNode(TAG_CHECKIN);
        tagStatus.appendChild(textStatus);

        QTextStream out(&file);
        out << xml.toString();
        file.close();
        QMessageBox::information(this,INFO,SUCCESS);
    }
}
/******************Hotel****************************
 ******************selectIdProof************************
 * @param none
 * @return none
 ****************************************************/
void Hotel::selectIdProof()
{
    QString fileName = QFileDialog::getOpenFileName(this,CAPTION, DIR, FILTER);
    if(!fileName.isEmpty())
    {
        ui->idProofLabel->setText(fileName);
    }

}

/******************Hotel****************************
 ******************openCustomer************************
 * @param none
 * Handling open customer action
 * @return none
 ****************************************************/
void Hotel::openCustomer()
{
    dlg = new CustomerDialog();
    connect(dlg,&CustomerDialog::searchSignal,this,&Hotel::searchCustomer);

    dlg->setModal(true);
    dlg->exec();
}

/******************Hotel****************************
 ******************searchCustomer************************
 * @param name - name of the customer
 * @param number- phone number of the customer
 * Based on name and number retreving the details of the customer
 * and emiting customerDialog signal to show the details in a qtreewidget
 * @return none
 ****************************************************/
void Hotel::searchCustomer(QString& name,QString& number)
{
    QString customerDetails;
    QDomDocument doc;
    QFile file("CustomerDetails.xml");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        if (doc.setContent(&file))
        {
            QDomNodeList rootNode = doc.elementsByTagName(TAG_CUSTOMER_DETAILS);

            if(rootNode.size()== 1)
            {
                QDomNodeList customersList = rootNode.at(0).childNodes();
                for (int i = 0; i < customersList.size(); ++i)
                {
                    QDomNodeList idNode = customersList.at(i).toElement().elementsByTagName(TAG_UID);
                    if(idNode.size() == 1)
                    {
                        if(name == idNode.at(0).toElement().attributeNode(TAG_NAME).value() &&
                                number == idNode.at(0).toElement().attributeNode(TAG_PHONE).value())
                        {
                            customerDetails = idNode.at(0).toElement().text();
                            dlg->showCustomerDetails(customerDetails);
                        }
                    }
                }
                file.close();
            }
            file.close();
        }
    }
    if(customerDetails.isEmpty())
    {
        QMessageBox::information(this,INFO,NO_RECORDS);
    }
}

