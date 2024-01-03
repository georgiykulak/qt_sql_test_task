#ifndef COUNTRIESOPERATORSMODEL_HPP
#define COUNTRIESOPERATORSMODEL_HPP

#include "TreeItemTypes.hpp"

#include <QAbstractItemModel>

#include <memory>

class TreeItem;
class SqlDatabaseModel;

class CountriesOperatorsModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit CountriesOperatorsModel(const QString& dbPath, QObject *parent = nullptr);

    bool setData(const QModelIndex &index,
                 const QVariant &value,
                 int role = Qt::EditRole) override;
    QVariant data(const QModelIndex &index,
                  int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    void DownloadSync();

public slots:
    // Required empty slot from task description
    void OnOperatorData(int mcc, int mnc);
    void getCountryCodeByMcc(int mcc, QString& code);

private:
    TreeItem* m_rootItem;
    std::shared_ptr<SqlDatabaseModel> m_databaseModel;

    void convertCountriesToTree();
};

#endif // COUNTRIESOPERATORSMODEL_HPP
