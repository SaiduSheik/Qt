#ifndef DEMOMODEL_H
#define DEMOMODEL_H

#include <QAbstractListModel>
#include <QObject>

class DemoSource;

class DemoModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(DemoSource *getSource READ getSource WRITE setSource)

public:
    explicit DemoModel(QObject *parent = nullptr);
    enum { ID = Qt::UserRole+1 };

    int         rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant    data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

    DemoSource      *getSource() const;
    void             setSource(DemoSource *source);

private:
    DemoSource      *m_pSource;
};

#endif // TODOMODEL_H
