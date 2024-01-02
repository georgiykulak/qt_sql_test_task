#include "TreeItem.hpp"

TreeItem::TreeItem(QObject *parent)
    : QObject{parent}
    , m_parentItem(nullptr)
{}

TreeItem::TreeItem(TreeItem *parentItem, QObject* parent)
    : QObject{parent}
    , m_parentItem(parentItem)
{}

TreeItem::TreeItem(const QVariant& data, TreeItem *parentItem, QObject* parent)
    : QObject{parent}
    , m_itemData(data)
    , m_parentItem(parentItem)
{}

TreeItem::~TreeItem()
{
    qDeleteAll(m_childItems);
}

void TreeItem::appendChild(TreeItem *item)
{
    m_childItems.append(item);
}

TreeItem *TreeItem::child(int row)
{
    if (row < 0 || row >= m_childItems.size())
        return nullptr;
    return m_childItems.at(row);
}

int TreeItem::childCount() const
{
    return m_childItems.count();
}

int TreeItem::columnCount() const
{
    return 1;
}

QVariant TreeItem::data(int /* column */) const
{
    return m_itemData;
}

void TreeItem::setData(const QVariant &itemData, int /* column */)
{
    m_itemData = itemData;
}

TreeItem *TreeItem::parentItem()
{
    return m_parentItem;
}

int TreeItem::row() const
{
    if (m_parentItem)
        return m_parentItem->m_childItems.indexOf(const_cast<TreeItem*>(this));

    return 0;
}
