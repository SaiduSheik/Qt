#include "demomodel.h"
#include "demosource.h"

/*****************DemoModel************************
 ******************Constructor************************
 * @param parent QObject
 * @return none
 ****************************************************/
DemoModel::DemoModel(QObject *parent)
    : QAbstractListModel(parent)
    , m_pSource(nullptr)
{

}

/*****************rowCount************************
 ******************rowCount************************
 * @param    parent is the model index
 * @return   number of rows in that source
 ****************************************************/
int DemoModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid() || !m_pSource)
        return 0;

    return m_pSource->getJobIDs().size();
}

/*****************data************************
 ******************data************************
 * @param  index
 * @param  role
 * @return QVariant returns the data based on index
 * and role
 ****************************************************/
QVariant DemoModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !m_pSource)
        return QVariant();

    if (index.row() >= m_pSource->getJobIDs().size() || index.row() < 0)
        return QVariant();

    switch (role)
    {
    case ID:
        return  QVariant(m_pSource->getJobIDs().at((index.row())));
    }

    return QVariant();
}

/*****************roleNames************************
 ******************roleNames************************
 * @param    none
 * return QHash<int, QByteArray> rolenames
 ****************************************************/
QHash<int, QByteArray> DemoModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[ID] = "id";
    return names;
}

/*****************getSource************************
 ******************getSource************************
 * @param    none
 * return DemoSource
 ****************************************************/
DemoSource *DemoModel::getSource() const
{
    return m_pSource;
}

/*****************setSource************************
 ******************setSource************************
 * @param DemoSource
 * return none
 ****************************************************/
void DemoModel::setSource(DemoSource *source)
{
    m_pSource = source;
}
