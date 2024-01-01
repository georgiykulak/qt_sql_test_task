#include "OperatorDataButton.hpp"

#include <QPainter>

OperatorDataButton::OperatorDataButton(QWidget *parent)
    : QWidget{parent}
{
    setMaximumSize(16, 16);
}

void OperatorDataButton::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    emit operatorData();
}

void OperatorDataButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    const auto pixSize = width() - 1;
    const auto halfPixSize = pixSize / 2;

    QRect rect(0, 0, pixSize, pixSize);
    QLine lineVertical(halfPixSize, 2, halfPixSize, pixSize - 2);
    QLine lineHorizontal(2, halfPixSize, pixSize - 2, halfPixSize);

    QPen mPen;
    mPen.setWidth(1);
    mPen.setBrush(Qt::darkGray);
    painter.setPen(mPen);

    painter.drawRoundedRect(rect, 2, 2);
    painter.drawLine(lineVertical);
    painter.drawLine(lineHorizontal);
}
