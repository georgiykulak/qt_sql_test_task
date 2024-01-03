#ifndef SQLDATABASEMODEL_HPP
#define SQLDATABASEMODEL_HPP

#include <model/TreeItemTypes.hpp>

#include <QObject>

#include <memory>

class QSqlDatabase;

class SqlDatabaseModel : public QObject
{
    Q_OBJECT
public:
    explicit SqlDatabaseModel(const QString& dbPath, QObject *parent = nullptr);

    void DownloadSync();
    Operators DownloadOperators(int mcc);
    const Countries& GetCountries() const;
    bool UpdateOperatorRecord(const Operator& oper);
    bool InsertOperatorRecord(const Operator& oper);

private:
    std::shared_ptr<QSqlDatabase> m_database;
    Countries m_countries;
    bool m_dbIsReady = false;

    QString queryWhereMccIs(int mcc) const;
};

#endif // SQLDATABASEMODEL_HPP
