#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <QString>
#include <QObject>

static const QString CAPTION = QObject::tr("Open Image");
static const QString DIR = QObject::tr("/home");
static const QString FILTER = QObject::tr("Image Files (*.png *.jpg *.bmp)");
static const QString PHOTO = QObject::tr("photo");
static const QString WARNING = QObject::tr("Warning");
static const QString WARNING_MSG = QObject::tr("Please provide customer name and phone number.");
static const QString DELIMITER = "$#$";
static const QString INFO = QObject::tr("Information");
static const QString TAG_CUSTOMER_DETAILS = QObject::tr("CustomerDetails");
static const QString TAG_CUSTOMER =QObject::tr("Customer");
static const QString TAG_UID = QObject::tr("UID");
static const QString TAG_NAME = QObject::tr("name");
static const QString TAG_PHONE = QObject::tr("phone");
static const QString TAG_ADDRESS=QObject::tr("address");
static const QString TAG_DAYS=QObject::tr("days");
static const QString TAG_ROOM_TYPE=QObject::tr("roomtype");
static const QString TAG_ID = QObject::tr("id");
static const QString TAG_STATUS = QObject::tr("status");
static const QString TAG_CHECKIN= QObject::tr("CheckedIn");
static const QString SUCCESS = QObject::tr("Success");

static const int COL_COUNT = 8;
static const QString NO_RECORDS = QObject::tr("No records found.");
static const QString SELECT_RECORD = QObject::tr("Please select customer to process the bill");


#endif // CONSTANTS_H
