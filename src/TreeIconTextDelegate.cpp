#include "TreeIconTextDelegate.hpp"
#include "TreeItemTypes.h"
#include "OperatorEditorDialog.hpp"

#include <QDebug>
#include <QPainter>
#include <QEvent>

TreeIconTextDelegate::TreeIconTextDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{}

void TreeIconTextDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
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

QSize TreeIconTextDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
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

bool TreeIconTextDelegate::editorEvent(QEvent *event,
                                       QAbstractItemModel *model,
                                       const QStyleOptionViewItem &option,
                                       const QModelIndex &index)
{
    if (index.data().canConvert<Operator>()
        && event->type() == QEvent::MouseButtonDblClick)
    {
        qDebug() << "TreeIconTextDelegate editorEvent: event type ->"
                 << event->type();

        OperatorEditorDialog* dialog = new OperatorEditorDialog(model);
        dialog->show();
    }

    return QStyledItemDelegate::editorEvent(event, model, option, index);
}
