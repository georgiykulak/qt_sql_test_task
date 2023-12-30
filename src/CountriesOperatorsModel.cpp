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
        qWarning() << "CountriesOperatorsModel: Can't initialize database";
        return;
    }

    m_database->setDatabaseName(dbPath);

    if (!m_database->open())
    {
        qWarning() << "CountriesOperatorsModel:" << m_database->lastError().text();
        return;
    }

    qDebug() << "CountriesOperatorsModel: Database is ready";
    m_dbIsReady = true;
}

///////////////////////////////////////////////////////////////////////////////
//////////////////// START OF ABSTRACT ITEM MODEL INTERFACE ///////////////////
///////////////////////////////////////////////////////////////////////////////

QVariant CountriesOperatorsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());

    return item->data();
}

Qt::ItemFlags CountriesOperatorsModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index);
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

    m_tableList = m_database->tables();
    auto tableListStr = m_tableList.join(", ");
    // TODO: Check required db tables - 'countries' and 'operators'

    qDebug() << "CountriesOperatorsModel DownloadSync: List of tables:" << tableListStr;

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

        qDebug() << "CountriesOperatorsModel DownloadSync: Country ->"
                 << mcc << name << code
                 << "| Operators: size ="
                 << operators.size() << stringify(operators);

        CountryData countryData;
        Country country;
        country.name = name;
        country.code = code;
        country.mcc = mcc;
        countryData.country = std::move(country);
        countryData.operators = std::move(operators);
        m_countries[mcc] = std::move(countryData);
    }

    convertCountriesToTree();
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
        op.name = name;
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
    m_rootItem = new TreeItem;

    for (auto&& [_, countryData] : m_countries)
    {
        QVariant country;
        country.setValue(countryData.country.name);
        auto* cItem = new TreeItem(country, m_rootItem);
        m_rootItem->appendChild(cItem);

        for (auto&& [name, _, mnc] : countryData.operators)
        {
            QVariant oper;
            oper.setValue(name);
            auto* oItem = new TreeItem(oper, cItem);
            cItem->appendChild(oItem);
        }
    }
}
