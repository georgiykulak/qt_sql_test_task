#ifndef COUNTRIESOPERATORSMODEL_HPP
#define COUNTRIESOPERATORSMODEL_HPP

#include "TreeItemTypes.hpp"

#include <QAbstractItemModel>

#include <memory>

class TreeItem;
class QSqlDatabase;

class CountriesOperatorsModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit CountriesOperatorsModel(const QString& dbPath, QObject *parent = nullptr);

    bool setData(const QModelIndex &index,
                 const QVariant &value,
                 int role) override;
    QVariant data(const QModelIndex &index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    void DownloadSync();

public slots:
    // Required empty slot from task description
    void onOperatorData(int mcc, int mnc);

private:
    Countries m_countries;
    TreeItem* m_rootItem;
    QStringList m_tableList;
    std::shared_ptr<QSqlDatabase> m_database;
    bool m_dbIsReady = false;

    Operators getOperators(int mcc);
    QString queryWhereMccIs(int mcc) const;
    bool updateOperatorRecord(const Operator& oper);
    bool insertOperatorRecord(const Operator& oper);
    QString stringify(const Operators& operators) const;
    void convertCountriesToTree();
};

#endif // COUNTRIESOPERATORSMODEL_HPP
