#ifndef TREEITEM_HPP
#define TREEITEM_HPP

#include <QVariant>
#include <QVector>

class TreeItem
{
public:
    explicit TreeItem(TreeItem *parentItem = nullptr);
    explicit TreeItem(const QVariant& data, TreeItem *parentItem = nullptr);
    ~TreeItem();

    void appendChild(TreeItem *child);
    TreeItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column = 0) const;
    int row() const;
    TreeItem *parentItem();

private:
    QVector<TreeItem*> m_childItems;
    QVariant m_itemData;
    TreeItem* m_parentItem;
};

#endif // TREEITEM_HPP
