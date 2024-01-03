#include "CountriesOperatorsModel.hpp"
#include "TreeItem.hpp"

#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

CountriesOperatorsModel::CountriesOperatorsModel(const QString& dbPath, QObject *parent)
    : QAbstractItemModel{parent}
    , m_database{new QSqlDatabase}
{
    *m_database = QSqlDatabase::addDatabase("QSQLITE");

    if (!m_database)
    {
        qCritical() << "CountriesOperatorsModel: Can't initialize database";
        return;
    }

    m_database->setDatabaseName(dbPath);

    if (!m_database->open())
    {
        qCritical() << "CountriesOperatorsModel:" << m_database->lastError().text();
        return;
    }

    qDebug() << "CountriesOperatorsModel: Database is ready";
    m_dbIsReady = true;
}

bool CountriesOperatorsModel::setData(const QModelIndex &index,
                                      const QVariant &value,
                                      int role)
{
    if (role == Qt::EditRole && value.canConvert<Operator>())
    {
        Operator oper = qvariant_cast<Operator>(value);
        const auto result = updateOperatorRecord(oper);

        if (!result)
            return false;

        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        beginResetModel();
        item->setData(value);
        endResetModel();

        return true;
    }
    else if (role == InsertRole && value.canConvert<Operator>())
    {
        const Operator oper = qvariant_cast<Operator>(value);
        const auto& allCountryItems = m_rootItem->childs();
        TreeItem* countryItem = nullptr;

        for (TreeItem* cItem : allCountryItems)
        {
            if ( !(cItem && cItem->data().canConvert<Country>()) )
                continue;

            Country country = qvariant_cast<Country>(cItem->data());
            if (country.mcc != oper.mcc)
                continue;

            // country.mcc == oper.mcc
            for (TreeItem* oItem : cItem->childs())
            {
                if ( !(oItem && oItem->data().canConvert<Operator>()) )
                    continue;

                // If operator with such 'mcc' and 'mnc' is already exists,
                // we should update it, not create copy of it with another name
                const Operator xOper = qvariant_cast<Operator>(oItem->data());
                if (xOper.mnc == oper.mnc)
                {
                    const auto result = updateOperatorRecord(oper);
                    if (result)
                    {
                        beginResetModel();
                        oItem->setData(value);
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

        const auto result = insertOperatorRecord(oper);

        if (!result)
            return false;

        const auto rowCount = countryItem->childCount();
        TreeItem* newOperItem = new TreeItem(value, countryItem);
        QModelIndex newOperIndex = createIndex(rowCount, 0, newOperItem);
        beginInsertRows(newOperIndex, rowCount, rowCount + 1);
        countryItem->appendChild(newOperItem);
        endInsertRows();
        return true;
    }

    return false;
}

///////////////////////////////////////////////////////////////////////////////
//////////////////// START OF ABSTRACT ITEM MODEL INTERFACE ///////////////////
///////////////////////////////////////////////////////////////////////////////

QVariant CountriesOperatorsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole && role != Qt::EditRole && role != InsertRole)
        return QVariant();

    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());

    return item->data();
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

    TreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, 0, childItem);
    return QModelIndex();
}

QModelIndex CountriesOperatorsModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem *parentItem = childItem->parentItem();

    if (parentItem == m_rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
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

    return parentItem->childCount();
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
    if (!m_dbIsReady)
        return;

    m_countries.clear();

    auto&& tableList = m_database->tables();

    const auto countriesAreMissing = !tableList.contains("countries");
    const auto operatorsAreMissing = !tableList.contains("operators");
    if (countriesAreMissing || operatorsAreMissing)
    {
        QStringList missingList;
        if (countriesAreMissing) missingList << "countries";
        if (operatorsAreMissing) missingList << "operators";

        qCritical() << "CountriesOperatorsModel DownloadSync: "
                       "Missing required tables:" << missingList.join(", ");
        return;
    }

    QSqlQuery queryAllCountries("SELECT * FROM 'countries'", *m_database);
    const auto fieldMcc = queryAllCountries.record().indexOf("mcc");
    const auto fieldName = queryAllCountries.record().indexOf("name");
    const auto fieldCode = queryAllCountries.record().indexOf("code");

    while (queryAllCountries.next())
    {
        const auto mcc = queryAllCountries.value(fieldMcc).toInt();
        const auto name = queryAllCountries.value(fieldName).toString();
        const auto code = queryAllCountries.value(fieldCode).toString();

        auto operators = getOperators(mcc);

        CountryData countryData;
        Country country;
        country.name = name.trimmed();
        country.code = code;
        country.mcc = mcc;
        countryData.country = std::move(country);
        countryData.operators = std::move(operators);
        m_countries[mcc] = std::move(countryData);
    }

    convertCountriesToTree();
}

void CountriesOperatorsModel::onOperatorData(int mcc, int mnc)
{
    qDebug() << "CountriesOperatorsModel onOperatorData: Received mcc =" << mcc
             << "mnc =" << mnc;
}

void CountriesOperatorsModel::getCountryCodeByMcc(int mcc, QString &code)
{
    const auto& allCountryItems = m_rootItem->childs();

    for (TreeItem* cItem : allCountryItems)
    {
        if (cItem && cItem->data().canConvert<Country>())
        {
            Country country = qvariant_cast<Country>(cItem->data());
            if (country.mcc == mcc)
            {
                code = country.code;
                return;
            }
        }
    }
}

Operators CountriesOperatorsModel::getOperators(int mcc)
{
    Operators operators;

    QSqlQuery queryOperators(queryWhereMccIs(mcc), *m_database);
    const auto fieldMnc = queryOperators.record().indexOf("mnc");
    const auto fieldMcc = queryOperators.record().indexOf("mcc");
    const auto fieldName = queryOperators.record().indexOf("name");

    while (queryOperators.next())
    {
        const auto mnc = queryOperators.value(fieldMnc).toInt();
        const auto mcc = queryOperators.value(fieldMcc).toInt();
        const auto name = queryOperators.value(fieldName).toString();

        Operator op;
        op.name = name.trimmed();
        op.mnc = mnc;
        op.mcc = mcc;
        operators.emplace_back(std::move(op));
    }

    return operators;
}

QString CountriesOperatorsModel::queryWhereMccIs(int mcc) const
{
    return QString("SELECT * FROM 'operators' WHERE mcc = %1 ORDER BY mnc ASC")
           .arg(mcc);
}

bool CountriesOperatorsModel::updateOperatorRecord(const Operator &oper)
{
    QSqlQuery updateOperator(*m_database);
    updateOperator.prepare("UPDATE 'operators' "
                           "SET name = :operName "
                           "WHERE mcc = :operMcc and mnc = :operMnc");
    updateOperator.bindValue(":operName", oper.name);
    updateOperator.bindValue(":operMcc", oper.mcc);
    updateOperator.bindValue(":operMnc", oper.mnc);
    return updateOperator.exec();
}

bool CountriesOperatorsModel::insertOperatorRecord(const Operator &oper)
{
    QSqlQuery insertOperator(*m_database);
    insertOperator.prepare("INSERT INTO 'operators' (name, mcc, mnc)"
                           "VALUES (:operName, :operMcc, :operMnc)");
    insertOperator.bindValue(":operName", oper.name);
    insertOperator.bindValue(":operMcc", oper.mcc);
    insertOperator.bindValue(":operMnc", oper.mnc);
    return insertOperator.exec();
}

QString CountriesOperatorsModel::stringify(const Operators &operators) const
{
    QString res;

    for (auto&& [name, _, mnc] : operators)
    {
        res.append(
            QString("{%1:'%2'} ").arg(mnc).arg(name)
        );
    }

    return res;
}

void CountriesOperatorsModel::convertCountriesToTree()
{
    m_rootItem = new TreeItem(nullptr, this);

    // Use root tree item as gateway for signals from delegate
    connect(m_rootItem, &TreeItem::operatorData,
            this, &CountriesOperatorsModel::onOperatorData);

    for (const auto& [_, countryData] : m_countries)
    {
        QVariant country(kCountryMetaId, &countryData.country);
        auto* cItem = new TreeItem(country, m_rootItem);
        m_rootItem->appendChild(cItem);

        for (const auto& op : countryData.operators)
        {
            QVariant oper(kOperatorMetaId, &op);
            auto* oItem = new TreeItem(oper, cItem);
            cItem->appendChild(oItem);
        }
    }
}
