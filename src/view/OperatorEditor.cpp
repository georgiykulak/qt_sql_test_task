#include "OperatorEditor.hpp"
#include <dialog/OperatorEditorDialog.hpp>
#include <view/buttons/OperatorDataButton.hpp>

#include <QDebug>
#include <QEvent>
#include <QPainter>
#include <QMouseEvent>

OperatorEditor::OperatorEditor(const Operator& op, QWidget *parent)
    : QWidget{parent}
    , m_operator{op}
{
    installEventFilter(this);
    setMouseTracking(true);
    setAutoFillBackground(true);

    m_operatorDataButton = new OperatorDataButton(this);
    m_operatorDataButton->move(m_operator.sizeHint().width(), 0);
    m_operatorDataButton->hide();

    connect(m_operatorDataButton, &OperatorDataButton::operatorData,
            this, &OperatorEditor::onOperatorData);
}

QSize OperatorEditor::sizeHint() const
{
    return m_operator.sizeHint() + m_operatorDataButton->sizeHint();
}

void OperatorEditor::onOperatorData()
{
    emit operatorData(m_operator.mcc, m_operator.mnc);
}

void OperatorEditor::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    m_operator.paint(&painter, rect(), palette());
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
        OperatorEditorDialog* dialog = new OperatorEditorDialog(nullptr, this);
        dialog->show();
    }
}
