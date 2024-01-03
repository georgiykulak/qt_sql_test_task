#include "SqlDatabaseModel.hpp"

#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

SqlDatabaseModel::SqlDatabaseModel(const QString& dbPath, QObject *parent)
    : QObject{parent}
    , m_database{new QSqlDatabase}
{
    if (!m_database)
    {
        qCritical() << "SqlDatabaseModel: Can't initialize database";
        return;
    }

    *m_database = QSqlDatabase::addDatabase("QSQLITE");
    m_database->setDatabaseName(dbPath);

    if (!m_database->open())
    {
        qCritical() << "SqlDatabaseModel:" << m_database->lastError().text();
        return;
    }

    qDebug() << "SqlDatabaseModel: Database is ready";
    m_dbIsReady = true;
}

void SqlDatabaseModel::DownloadSync()
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

        qCritical() << "SqlDatabaseModel DownloadSync: "
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

        auto operators = DownloadOperators(mcc);

        CountryData countryData;
        Country country;
        country.name = name.trimmed();
        country.code = code;
        country.mcc = mcc;
        countryData.country = std::move(country);
        countryData.operators = std::move(operators);
        m_countries[mcc] = std::move(countryData);
    }
}

Operators SqlDatabaseModel::DownloadOperators(int mcc)
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

const Countries &SqlDatabaseModel::GetCountries() const
{
    return m_countries;
}

bool SqlDatabaseModel::UpdateOperatorRecord(const Operator &oper)
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

bool SqlDatabaseModel::InsertOperatorRecord(const Operator &oper)
{
    QSqlQuery insertOperator(*m_database);
    insertOperator.prepare("INSERT INTO 'operators' (name, mcc, mnc)"
                           "VALUES (:operName, :operMcc, :operMnc)");
    insertOperator.bindValue(":operName", oper.name);
    insertOperator.bindValue(":operMcc", oper.mcc);
    insertOperator.bindValue(":operMnc", oper.mnc);
    return insertOperator.exec();
}

QString SqlDatabaseModel::queryWhereMccIs(int mcc) const
{
    return QString("SELECT * FROM 'operators' WHERE mcc = %1 ORDER BY mnc ASC")
        .arg(mcc);
}
