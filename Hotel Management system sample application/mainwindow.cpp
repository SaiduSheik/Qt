#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_customerDlg.h"

#include <QFileDialog>
#include <QTextStream>
#include<QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->CustomerDetails_GrpBox->hide();


    connect(ui->photoLabel,&ClickableLabel::clicked,this,&MainWindow::browsePhoto);
    connect(ui->actionNew,&QAction::triggered,this,&MainWindow::createNewCustomer);
    connect(ui->clearButton,&QPushButton::clicked,this,&MainWindow::clearCustomerDetails);
    connect(ui->submitButton,&QPushButton::clicked,this,&MainWindow::saveCustomerDetails);
    connect(ui->idProofToolButton,&QToolButton::clicked,this,&MainWindow::selectIdProof);
    connect(ui->actionOpen,&QAction::triggered,this,&MainWindow::openCustomer);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::browsePhoto()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Image"), "/home/jana", tr("Image Files (*.png *.jpg *.bmp)"));
    if(!fileName.isEmpty() && m_strImagePath != fileName)
    {
        ui->photoLabel->setScaledContents(true);
        ui->photoLabel->setPixmap(QPixmap(fileName).scaled(ui->photoLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        m_strImagePath = fileName;
    }
}

void MainWindow::createNewCustomer()
{
    clearCustomerDetails();
    ui->CustomerDetails_GrpBox->show();
}
void MainWindow::clearCustomerDetails()
{
    ui->customerNameEdit->clear();
    ui->customerAddressEdit->clear();
    ui->numOfDaysspinBox->clear();
    ui->typeOfRoomcomboBox->setCurrentText("");
    ui->idProofLabel->setText("");
    ui->photoLabel->setText("Photo");
    ui->phNumEdit->clear();
}
void MainWindow::saveCustomerDetails()
{
    if(ui->customerNameEdit->text().isEmpty() || ui->phNumEdit->text().isEmpty())
    {
        QMessageBox::warning(this,"warning","please provide name and phone number");
        return;
    }
    const QString DELIMITER = "$#$";
    QDomDocument xml;
    QDomElement rootText;

    QFile file("CustomerDetails.xml");
    if(file.open(QIODevice::ReadOnly) && xml.setContent(&file))
    {
        if(xml.elementsByTagName("CustomerDetails").size() > 0)
        {
            rootText = xml.elementsByTagName("CustomerDetails").at(0).toElement();
        }
    }
    else
    {
        rootText = xml.createElement("CustomerDetails");

    }
    file.close();
    xml.appendChild(rootText);
    if (file.open(QIODevice::WriteOnly| QIODevice::Text | QIODevice::Truncate))
    {
        QDomElement custEle = xml.createElement("Customer");
        rootText.appendChild(custEle);

        QDomElement root = xml.createElement("ID");
        root.setAttribute("phone",ui->phNumEdit->text());
        root.setAttribute("name",ui->customerNameEdit->text());
        custEle.appendChild(root);

        QDomElement tagName = xml.createElement("name");
        root.appendChild(tagName);
        QDomText textName = xml.createTextNode(ui->customerNameEdit->text()+DELIMITER);
        tagName.appendChild(textName);

        QDomElement tagPhone = xml.createElement("phone");
        root.appendChild(tagPhone);
        QDomText textPhone = xml.createTextNode((ui->phNumEdit->text() + DELIMITER));
        tagPhone.appendChild(textPhone);

        QDomElement tagAddress = xml.createElement("address");
        root.appendChild(tagAddress);
        QDomText textAddress = xml.createTextNode(ui->customerAddressEdit->text()+DELIMITER);
        tagAddress.appendChild(textAddress);

        QDomElement tagDays = xml.createElement("days");
        root.appendChild(tagDays);
        QDomText textDays = xml.createTextNode(ui->numOfDaysspinBox->text()+DELIMITER);
        tagDays.appendChild(textDays);

        QDomElement tagRoomType = xml.createElement("roomtype");
        root.appendChild(tagRoomType);
        QDomText textRoomType = xml.createTextNode(ui->typeOfRoomcomboBox->currentText()+DELIMITER);
        tagRoomType.appendChild(textRoomType);

        QDomElement tagId = xml.createElement("id");
        root.appendChild(tagId);
        QDomText textId = xml.createTextNode(ui->idProofLabel->text()+DELIMITER);
        tagId.appendChild(textId);

        QDomElement tagPhoto = xml.createElement("photo");
        root.appendChild(tagPhoto);
        QDomText textPhoto = xml.createTextNode(m_strImagePath+DELIMITER);
        tagPhoto.appendChild(textPhoto);

        QDomElement tagStatus = xml.createElement("status");
        root.appendChild(tagStatus);
        QDomText textStatus = xml.createTextNode("CheckedIn");
        tagStatus.appendChild(textStatus);

        QTextStream out(&file);
        out << xml.toString();
        file.close();
        QMessageBox::information(this,"info","success");
    }
}
void MainWindow::selectIdProof()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Image"), "/home/jana", tr("Image Files (*.png *.jpg *.bmp)"));
    if(!fileName.isEmpty())
    {
        ui->idProofLabel->setText(fileName);
    }

}

void MainWindow::openCustomer()
{
    dlg = new CustomerDialog();
    connect(dlg,&CustomerDialog::searchSignal,this,&MainWindow::searchCustomer);

    dlg->setModal(true);
    dlg->exec();
}

void MainWindow::searchCustomer(QString& name,QString& number)
{
    QDomDocument doc;
    QFile file("CustomerDetails.xml");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        if (doc.setContent(&file))
        {
            QString customerDetails;
            QDomNodeList rootNode = doc.elementsByTagName("CustomerDetails");

            if(rootNode.size()== 1)
            {
                QDomNodeList customersList = rootNode.at(0).childNodes();
                for (int i = 0; i < customersList.size(); ++i)
                {
                    QDomNodeList idNode = customersList.at(i).toElement().elementsByTagName("ID");
                    if(idNode.size() == 1)
                    {
                        if(name == idNode.at(0).toElement().attributeNode("name").value() &&
                           number == idNode.at(0).toElement().attributeNode("phone").value())
                        {
                            customerDetails = idNode.at(0).toElement().text();
                            dlg->showCustomerDetails(customerDetails);
                        }
                    }
                }
                file.close();
                return;
            }
            file.close();
        }
    }
}

