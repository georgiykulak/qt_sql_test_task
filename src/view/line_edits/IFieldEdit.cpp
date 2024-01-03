#include "IFieldEdit.hpp"

#include <QLineEdit>
#include <QPainter>
#include <QResizeEvent>

IFieldEdit::IFieldEdit(const QColor& bg,
                       QWidget* parent)
    : QWidget{parent}
{
    m_lineEdit = new QLineEdit(this);
    m_lineEdit->setStyleSheet("background-color: " + bg.name());
    m_lineEdit->setFrame(false);
    m_lineEdit->move(2, 2);

    setSizePolicy(m_lineEdit->sizePolicy());

    connect(m_lineEdit, &QLineEdit::textChanged,
            this, &IFieldEdit::onTextChanged);
}

QSize IFieldEdit::sizeHint() const
{
    return m_lineEdit->sizeHint() + m_margin;
}

void IFieldEdit::setDisabled()
{
    m_lineEdit->setEnabled(false);
}

void IFieldEdit::setText(const QString &text)
{
    m_lineEdit->setText(text);
}

void IFieldEdit::setValid(bool valid)
{
    m_valid = valid;
    update();
    emit validStateChanged(valid);
}

void IFieldEdit::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    drawValidityFrame(painter);
}

void IFieldEdit::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    m_lineEdit->resize(event->size() - m_margin);
}

void IFieldEdit::enableClearButton()
{
    m_lineEdit->setClearButtonEnabled(true);
}

void IFieldEdit::drawValidityFrame(QPainter& painter) const
{
    QPen pen;

    if (m_valid)
    {
        pen.setBrush(Qt::darkGray);
        pen.setWidth(1);
        painter.setPen(pen);
    }
    else
    {
        pen.setBrush(Qt::red);
        pen.setWidth(3);
        painter.setPen(pen);
    }

    painter.drawRect(0, 0, width() - 1, height() - 1);
}
