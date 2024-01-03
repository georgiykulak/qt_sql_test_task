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
    explicit TreeItem(TreeItem *ParentItem = nullptr, QObject* parent = nullptr);
    explicit TreeItem(const QVariant& data,
                      TreeItem *ParentItem = nullptr,
                      QObject* parent = nullptr);
    virtual ~TreeItem();

    void AppendChild(TreeItem *child);
    TreeItem *Child(int row);
    const QVector<TreeItem*>& Childs() const;
    int ChildCount() const;
    QVariant Data() const;
    void SetData(const QVariant& itemData, int column = 0);
    int Row() const;
    TreeItem *ParentItem();

signals:
    void operatorData(int mcc, int mnc);

private:
    QVector<TreeItem*> m_childItems;
    QVariant m_itemData;
    TreeItem* m_parentItem;
};

#endif // TREEITEM_HPP
