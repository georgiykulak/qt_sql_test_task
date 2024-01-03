#ifndef TREEICONTEXTDELEGATE_HPP
#define TREEICONTEXTDELEGATE_HPP

#include <QStyledItemDelegate>

class CountriesOperatorsModel;

class TreeIconTextDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    using QStyledItemDelegate::QStyledItemDelegate;

    explicit TreeIconTextDelegate(
        std::shared_ptr<CountriesOperatorsModel> rootModel,
        QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const override;
    // For operators only
    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;
    void setEditorData(QWidget *editor,
                       const QModelIndex &index) const override;
    void setModelData(QWidget *editor,
                      QAbstractItemModel *model,
                      const QModelIndex &index) const override;

private:
    std::shared_ptr<CountriesOperatorsModel> m_rootModel;
};

#endif // TREEICONTEXTDELEGATE_HPP
