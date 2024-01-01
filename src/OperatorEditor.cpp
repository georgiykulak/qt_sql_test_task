#include "OperatorEditor.hpp"
#include "AddOperatorButton.hpp"
#include "OperatorEditorDialog.hpp"

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

    m_addOperatorButton = new AddOperatorButton(this);
    m_addOperatorButton->move(m_operator.sizeHint().width(), 0);
    m_addOperatorButton->hide();

    connect(m_addOperatorButton, &AddOperatorButton::operatorData,
            this, &OperatorEditor::onOperatorData);
}

QSize OperatorEditor::sizeHint() const
{
    return m_operator.sizeHint() + m_addOperatorButton->sizeHint();
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
            m_addOperatorButton->show();
        }
        else if (event->type() == QEvent::Leave)
        {
            m_addOperatorButton->hide();
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
