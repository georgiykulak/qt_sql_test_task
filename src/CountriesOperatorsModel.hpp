#ifndef COUNTRIESOPERATORSMODEL_HPP
#define COUNTRIESOPERATORSMODEL_HPP

#include <QAbstractItemModel>
#include <QString>

#include <memory>
#include <vector>

class QSqlDatabase;

class CountriesOperatorsModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    using Operators = std::vector<std::pair<int, QString>>;
    struct CountryData
    {
        QString name;
        QString code;
        CountriesOperatorsModel::Operators operators;
    };
    using Countries = std::map<int, CountryData>;

    explicit CountriesOperatorsModel(const QString& dbPath, QObject *parent = nullptr);

    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    void DownloadSync();

private:
    Countries m_countries;
    QStringList m_tableList;
    std::shared_ptr<QSqlDatabase> m_database;
    bool m_dbIsReady = false;

    Operators getOperators(int mcc);
    QString queryWhereMccIs(int mcc) const;
    QString stringify(const Operators& operators) const;
};

#endif // COUNTRIESOPERATORSMODEL_HPP
