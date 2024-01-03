#include "OperatorEditor.hpp"
#include <model/TreeItem.hpp>
#include <model/CountriesOperatorsModel.hpp>
#include <dialog/OperatorEditorDialog.hpp>
#include <view/buttons/OperatorDataButton.hpp>

#include <QDebug>
#include <QEvent>
#include <QPainter>
#include <QMouseEvent>
#include <QAbstractItemModel>

OperatorEditor::OperatorEditor(std::shared_ptr<CountriesOperatorsModel> model,
                               const QModelIndex* index,
                               QWidget *parent)
    : QWidget{parent}
    , m_rootModel{model}
    , m_index{index}
{
    installEventFilter(this);
    setMouseTracking(true);
    setAutoFillBackground(true);

    m_operatorDataButton = new OperatorDataButton(this);
    Operator oper = qvariant_cast<Operator>(m_index->data());
    m_operatorDataButton->move(oper.sizeHint().width(), 0);
    m_operatorDataButton->hide();

    connect(m_operatorDataButton, &OperatorDataButton::operatorData,
            this, &OperatorEditor::onOperatorData);
}

QSize OperatorEditor::sizeHint() const
{
    Operator oper = qvariant_cast<Operator>(m_index->data());
    return oper.sizeHint() + m_operatorDataButton->sizeHint();
}

void OperatorEditor::setOperator(const Operator &op)
{
    TreeItem *item = static_cast<TreeItem*>(m_index->internalPointer());
    QVariant oper(kOperatorMetaId, &op);
    item->setData(oper);
}

Operator OperatorEditor::getOperator() const
{
    return qvariant_cast<Operator>(m_index->data());
}

void OperatorEditor::onOperatorData()
{
    Operator oper = qvariant_cast<Operator>(m_index->data());
    emit operatorData(oper.mcc, oper.mnc);
}

void OperatorEditor::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    Operator oper = qvariant_cast<Operator>(m_index->data());
    oper.paint(&painter, rect(), palette());
}

bool OperatorEditor::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == this)
    {
        if (event->type() == QEvent::Enter)
        {
            m_operatorDataButton->show();
        }
        else if (event->type() == QEvent::Leave)
        {
            m_operatorDataButton->hide();
        }
    }

    return false;
}

void OperatorEditor::mousePressEvent(QMouseEvent *event)
{
    if (event->type() == QEvent::MouseButtonDblClick)
    {
        OperatorEditorDialog* dialog
            = new OperatorEditorDialog(m_rootModel, m_index, this);
        dialog->show();
    }
}
