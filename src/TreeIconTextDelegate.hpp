#ifndef TREEICONTEXTDELEGATE_HPP
#define TREEICONTEXTDELEGATE_HPP

#include <QStyledItemDelegate>

class TreeIconTextDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    using QStyledItemDelegate::QStyledItemDelegate;

    explicit TreeIconTextDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const override;
};

#endif // TREEICONTEXTDELEGATE_HPP
