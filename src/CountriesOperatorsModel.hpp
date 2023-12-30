#ifndef COUNTRIESOPERATORSMODEL_HPP
#define COUNTRIESOPERATORSMODEL_HPP

#include <QObject>

#include <memory>
#include <vector>

class QSqlDatabase;

class CountriesOperatorsModel : public QObject
{
    Q_OBJECT
public:
    using Operators = std::vector<std::pair<int, QString>>;

    explicit CountriesOperatorsModel(const QString& dbPath, QObject *parent = nullptr);
    void DownloadSync();

private:
    std::shared_ptr<QSqlDatabase> m_database;
    QStringList m_tableList;
    bool m_dbIsReady = false;

    Operators getOperators(int mcc);
    QString queryWhereMccIs(int mcc) const;
    QString stringify(const Operators& operators) const;
};

#endif // COUNTRIESOPERATORSMODEL_HPP
