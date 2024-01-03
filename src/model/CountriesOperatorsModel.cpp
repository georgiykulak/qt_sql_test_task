#include "CountriesOperatorsModel.hpp"
#include <model/SqlDatabaseModel.hpp>
#include "TreeItem.hpp"

#include <QDebug>

CountriesOperatorsModel::CountriesOperatorsModel(const QString& dbPath, QObject *parent)
    : QAbstractItemModel{parent}
    , m_databaseModel{new SqlDatabaseModel(dbPath)}
{}

///////////////////////////////////////////////////////////////////////////////
//////////////////// START OF ABSTRACT ITEM MODEL INTERFACE ///////////////////
///////////////////////////////////////////////////////////////////////////////

bool CountriesOperatorsModel::setData(const QModelIndex &index,
                                      const QVariant &value,
                                      int role)
{
    if (role == Qt::EditRole && value.canConvert<Operator>())
    {
        Operator oper = qvariant_cast<Operator>(value);
        const auto result = m_databaseModel->UpdateOperatorRecord(oper);

        if (!result)
            return false;

        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        beginResetModel();
        item->SetData(value);
        endResetModel();

        return true;
    }
    else if (role == InsertRole && value.canConvert<Operator>())
    {
        const Operator oper = qvariant_cast<Operator>(value);
        const auto& allCountryItems = m_rootItem->Childs();
        TreeItem* countryItem = nullptr;

        for (TreeItem* cItem : allCountryItems)
        {
            if ( !(cItem && cItem->Data().canConvert<Country>()) )
                continue;

            Country country = qvariant_cast<Country>(cItem->Data());
            if (country.mcc != oper.mcc)
                continue;

            // country.mcc == oper.mcc
            for (TreeItem* oItem : cItem->Childs())
            {
                if ( !(oItem && oItem->Data().canConvert<Operator>()) )
                    continue;

                // If operator with such 'mcc' and 'mnc' is already exists,
                // we should update it, not create copy of it with another name
                const Operator xOper = qvariant_cast<Operator>(oItem->Data());
                if (xOper.mnc == oper.mnc)
                {
                    const auto result
                        = m_databaseModel->UpdateOperatorRecord(oper);
                    if (result)
                    {
                        beginResetModel();
                        oItem->SetData(value);
                        endResetModel();
                    }

                    return result;
                }
            }

            countryItem = cItem;
            break;
        }

        if (!countryItem)
            return false;

        const auto result = m_databaseModel->InsertOperatorRecord(oper);

        if (!result)
            return false;

        TreeItem* newOperItem = new TreeItem(value, countryItem);
        beginResetModel();
        countryItem->AppendChild(newOperItem);
        endResetModel();
        return true;
    }

    return false;
}

QVariant CountriesOperatorsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole && role != Qt::EditRole && role != InsertRole)
        return QVariant();

    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());

    return item->Data();
}

Qt::ItemFlags CountriesOperatorsModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return (Qt::ItemIsSelectable
          | Qt::ItemIsEditable
          | Qt::ItemIsDragEnabled
          | Qt::ItemIsDropEnabled
          | Qt::ItemIsEnabled);
}

QModelIndex CountriesOperatorsModel::index(int row, int /* column */, const QModelIndex &parent) const
{
    if (!hasIndex(row, 0, parent))
        return QModelIndex();

    TreeItem *parentItem;

    if (!parent.isValid())
        parentItem = m_rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    TreeItem *childItem = parentItem->Child(row);
    if (childItem)
        return createIndex(row, 0, childItem);
    return QModelIndex();
}

QModelIndex CountriesOperatorsModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem *parentItem = childItem->ParentItem();

    if (parentItem == m_rootItem)
        return QModelIndex();

    return createIndex(parentItem->Row(), 0, parentItem);
}

int CountriesOperatorsModel::rowCount(const QModelIndex &parent) const
{
    TreeItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = m_rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    return parentItem->ChildCount();
}

int CountriesOperatorsModel::columnCount(const QModelIndex& /* parent */) const
{
    return 1;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////// END OF ABSTRACT ITEM MODEL INTERFACE ////////////////////
///////////////////////////////////////////////////////////////////////////////

void CountriesOperatorsModel::DownloadSync()
{
    m_databaseModel->DownloadSync();

    convertCountriesToTree();
}

void CountriesOperatorsModel::OnOperatorData(int mcc, int mnc)
{
    qDebug() << "CountriesOperatorsModel OnOperatorData: Received mcc =" << mcc
             << "mnc =" << mnc;
}

void CountriesOperatorsModel::getCountryCodeByMcc(int mcc, QString &code)
{
    const auto& allCountryItems = m_rootItem->Childs();

    for (TreeItem* cItem : allCountryItems)
    {
        if (cItem && cItem->Data().canConvert<Country>())
        {
            Country country = qvariant_cast<Country>(cItem->Data());
            if (country.mcc == mcc)
            {
                code = country.code;
                return;
            }
        }
    }
}

void CountriesOperatorsModel::convertCountriesToTree()
{
    m_rootItem = new TreeItem(nullptr, this);

    // Use root tree item as gateway for signals from delegate
    connect(m_rootItem, &TreeItem::operatorData,
            this, &CountriesOperatorsModel::OnOperatorData);

    for (const auto& [_, countryData] : m_databaseModel->GetCountries())
    {
        QVariant country(kCountryMetaId, &countryData.country);
        auto* cItem = new TreeItem(country, m_rootItem);
        m_rootItem->AppendChild(cItem);

        for (const auto& op : countryData.operators)
        {
            QVariant oper(kOperatorMetaId, &op);
            auto* oItem = new TreeItem(oper, cItem);
            cItem->AppendChild(oItem);
        }
    }
}
