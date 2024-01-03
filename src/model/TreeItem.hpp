#ifndef TREEITEM_HPP
#define TREEITEM_HPP

#include <QObject>
#include <QVariant>
#include <QVector>

class TreeItem : public QObject
{
    Q_OBJECT
public:
    explicit TreeItem(QObject* parent = nullptr);
    explicit TreeItem(TreeItem *parentItem = nullptr, QObject* parent = nullptr);
    explicit TreeItem(const QVariant& data,
                      TreeItem *parentItem = nullptr,
                      QObject* parent = nullptr);
    virtual ~TreeItem();

    void appendChild(TreeItem *child);
    TreeItem *child(int row);
    const QVector<TreeItem*>& childs() const;
    int childCount() const;
    QVariant data() const;
    void setData(const QVariant& itemData, int column = 0);
    int row() const;
    TreeItem *parentItem();

signals:
    void operatorData(int mcc, int mnc);

private:
    QVector<TreeItem*> m_childItems;
    QVariant m_itemData;
    TreeItem* m_parentItem;
};

#endif // TREEITEM_HPP
