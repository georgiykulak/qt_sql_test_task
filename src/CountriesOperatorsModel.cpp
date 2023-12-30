#include "CountriesOperatorsModel.hpp"

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

QModelIndex CountriesOperatorsModel::index(int row, int column, const QModelIndex &parent) const
{
    // TODO
}

QModelIndex CountriesOperatorsModel::parent(const QModelIndex &child) const
{
    // TODO
}

int CountriesOperatorsModel::rowCount(const QModelIndex &parent) const
{
    // TODO
}

int CountriesOperatorsModel::columnCount(const QModelIndex &parent) const
{
    // TODO
}

QVariant CountriesOperatorsModel::data(const QModelIndex &index, int role) const
{
    // TODO
}

QVariant CountriesOperatorsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();
}

Qt::ItemFlags CountriesOperatorsModel::flags(const QModelIndex &index) const
{
    // TODO
}

void CountriesOperatorsModel::DownloadSync()
{
    if (!m_dbIsReady)
        return;

    beginResetModel();

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
    }

    endResetModel();
}

CountriesOperatorsModel::Operators CountriesOperatorsModel::getOperators(int mcc)
{
    Operators operators;

    QSqlQuery queryOperators(queryWhereMccIs(mcc), *m_database);
    const auto fieldMnc = queryOperators.record().indexOf("mnc");
    const auto fieldName = queryOperators.record().indexOf("name");

    while (queryOperators.next())
    {
        const auto mnc = queryOperators.value(fieldMnc).toInt();
        const auto name = queryOperators.value(fieldName).toString();
        operators.emplace_back(std::make_pair(mnc, name));
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

    for (auto&& [mnc, name] : operators)
    {
        res.append(
            QString("{%1:'%2'} ").arg(mnc).arg(name)
        );
    }

    return res;
}
