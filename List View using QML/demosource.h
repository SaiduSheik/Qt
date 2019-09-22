#ifndef DEMOSOURCE_H
#define DEMOSOURCE_H

#include <QObject>

class QNetworkReply;

class DemoSource : public QObject
{
    Q_OBJECT
public:
    explicit DemoSource(QObject *parent = nullptr);
             ~DemoSource();

    Q_INVOKABLE void showDetails(int);
    QVector<int> getJobIDs() const;

private:
    QVector<int>           m_VecJobIDs;
};
#endif // DEMOSOURCE_H
