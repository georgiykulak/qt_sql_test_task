#include "TreeItem.hpp"

TreeItem::TreeItem(QObject *parent)
    : QObject{parent}
    , m_parentItem(nullptr)
{}

TreeItem::TreeItem(TreeItem *ParentItem, QObject* parent)
    : QObject{parent}
    , m_parentItem(ParentItem)
{}

TreeItem::TreeItem(const QVariant& data, TreeItem *ParentItem, QObject* parent)
    : QObject{parent}
    , m_itemData(data)
    , m_parentItem(ParentItem)
{}

TreeItem::~TreeItem()
{
    qDeleteAll(m_childItems);
}

void TreeItem::AppendChild(TreeItem *child)
{
    m_childItems.append(child);
}

TreeItem *TreeItem::Child(int row)
{
    if (row < 0 || row >= m_childItems.size())
        return nullptr;
    return m_childItems.at(row);
}

const QVector<TreeItem*>& TreeItem::Childs() const
{
    return m_childItems;
}

int TreeItem::ChildCount() const
{
    return m_childItems.count();
}

QVariant TreeItem::Data() const
{
    return m_itemData;
}

void TreeItem::SetData(const QVariant &itemData, int /* column */)
{
    m_itemData = itemData;
}

TreeItem *TreeItem::ParentItem()
{
    return m_parentItem;
}

int TreeItem::Row() const
{
    if (m_parentItem)
        return m_parentItem->m_childItems.indexOf(const_cast<TreeItem*>(this));

    return 0;
}
