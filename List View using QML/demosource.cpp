#include "demosource.h"

#include <QDesktopServices>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
/*****************DemoSource************************
 ******************Constructor************************
 * @param parent QObject
 * @return none
 ****************************************************/
DemoSource::DemoSource(QObject *parent) : QObject(parent)
{
    QString strIds = "[ 21040625, 21039838, 21040493, 21037811, 21039748, 21039255, 21039191, 21040696, 21033951, 21027730, 21041430, 21039982, 21024941, 21037919, 21035171, 21039189, 21020168, 21005372, 21035686, 21035477, 21024358, 21029792, 21032965, 21024366, 21037382, 21012722, 21032945, 21030751, 21030116, 21019016, 21026018, 21025034, 20989834, 21023072, 21022169, 21002950 ]";
    strIds = strIds.mid(1,strIds.size()-2);
    QStringList strlstId = strIds.split(",",QString::SkipEmptyParts);
    for(int i=0;i<strlstId.size();i++)
    {
        m_VecJobIDs.append(strlstId.at(i).toInt());
    }
}

/*****************~DemoSource************************
 ******************Destructor************************
 * @param    none
 * @return   none
 ****************************************************/
DemoSource::~DemoSource()
{

}

/*****************************************************
 * ***************getJobIDs***************************
 * @param : none
 * @return vector of job IDs
 ****************************************************/
QVector<int> DemoSource::getJobIDs() const
{
    return m_VecJobIDs;
}

/********************showDetails***********************
 * To show the details description of a particular job
 * @param index
 * Based on this index get job Id from vector
 * @return none
 ****************************************************/
void DemoSource::showDetails(int index)
{
    if(index >= 0 && index < m_VecJobIDs.size())
    {
        //composing URL based on job id
        QString link = QString("https://hacker-news.firebaseio.com/v0/item/%1.json?print=pretty")
                     .arg(QString::number((m_VecJobIDs.at((index)))));

        QDesktopServices::openUrl(QUrl(link));
    }
}


