#include "TreeIconTextDelegate.hpp"
#include "TreeItemTypes.hpp"
#include "TreeItem.hpp"
#include "OperatorEditor.hpp"

#include <QDebug>
#include <QPainter>
#include <QEvent>

TreeIconTextDelegate::TreeIconTextDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{}

void TreeIconTextDelegate::paint(QPainter *painter,
                                 const QStyleOptionViewItem &option,
                                 const QModelIndex &index) const
{
    if (index.data().canConvert<Country>())
    {
        Country country = qvariant_cast<Country>(index.data());

        if (option.state & QStyle::State_Selected)
            painter->fillRect(option.rect, option.palette.highlight());

        country.paint(painter, option.rect, option.palette);
    }
    else if (index.data().canConvert<Operator>())
    {
        Operator oper = qvariant_cast<Operator>(index.data());

        if (option.state & QStyle::State_Selected)
            painter->fillRect(option.rect, option.palette.highlight());

        oper.paint(painter, option.rect, option.palette);
    }
    else
    {
        QStyledItemDelegate::paint(painter, option, index);
    }
}

QSize TreeIconTextDelegate::sizeHint(const QStyleOptionViewItem &option,
                                     const QModelIndex &index) const
{
    if (index.data().canConvert<Country>())
    {
        Country country = qvariant_cast<Country>(index.data());
        return country.sizeHint();
    }
    else if (index.data().canConvert<Operator>())
    {
        Operator oper = qvariant_cast<Operator>(index.data());
        return oper.sizeHint();
    }

    return QStyledItemDelegate::sizeHint(option, index);
}

QWidget* TreeIconTextDelegate::createEditor(QWidget *parent,
                                            const QStyleOptionViewItem &option,
                                            const QModelIndex &index) const
{
    Q_UNUSED(option);

    if (index.data().canConvert<Operator>())
    {
        Operator oper = qvariant_cast<Operator>(index.data());
        OperatorEditor* operEditor = new OperatorEditor(oper, parent);
        TreeItem* item = static_cast<TreeItem*>(index.internalPointer());

        if (!item)
            return operEditor;

        TreeItem* parentItem = item->parentItem();

        // Go to root item, which is gateway for signals
        while (parentItem)
        {
            item = parentItem;
            parentItem = parentItem->parentItem();
        }

        connect(operEditor, &OperatorEditor::operatorData,
                item, &TreeItem::operatorData);

        return operEditor;
    }

    return nullptr;
}

void TreeIconTextDelegate::setEditorData(QWidget *editor,
                                         const QModelIndex &index) const
{
    if (index.data().canConvert<Operator>())
    {
        Operator oper = qvariant_cast<Operator>(index.data());
        OperatorEditor* operEditor = qobject_cast<OperatorEditor*>(editor);
        operEditor->setOperator(oper);
    }
}

void TreeIconTextDelegate::setModelData(QWidget *editor,
                                        QAbstractItemModel *model,
                                        const QModelIndex &index) const
{
    if (index.data().canConvert<Operator>())
    {
        OperatorEditor* operEditor = qobject_cast<OperatorEditor*>(editor);
        model->setData(index, QVariant::fromValue(operEditor->getOperator()));
    }
}
