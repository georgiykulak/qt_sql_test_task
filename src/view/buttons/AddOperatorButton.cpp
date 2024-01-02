#include "AddOperatorButton.hpp"
#include <dialog/OperatorEditorDialog.hpp>

#include <QPainter>

AddOperatorButton::AddOperatorButton(std::shared_ptr<QAbstractItemModel> model,
                                     QWidget *parent)
    : QWidget{parent}
    , m_model{model}
{
    setMinimumSize(20, 20);
    setMaximumSize(20, 20);
}

void AddOperatorButton::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    OperatorEditorDialog* dialog
        = new OperatorEditorDialog(m_model, nullptr, this);
    dialog->show();
}

void AddOperatorButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    const auto pixSize = width();
    const auto halfPixSize = pixSize / 2;

    QLine lineVertical(halfPixSize, 2, halfPixSize, pixSize - 2);
    QLine lineHorizontal(2, halfPixSize, pixSize - 2, halfPixSize);

    QPen mPen;
    mPen.setWidth(3);
    mPen.setBrush(Qt::black);
    painter.setPen(mPen);

    painter.drawLine(lineVertical);
    painter.drawLine(lineHorizontal);
}
