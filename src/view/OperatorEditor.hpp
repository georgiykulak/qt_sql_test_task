#ifndef OPERATOREDITOR_HPP
#define OPERATOREDITOR_HPP

#include <model/TreeItemTypes.hpp>

#include <QWidget>

class OperatorDataButton;

class OperatorEditor : public QWidget
{
    Q_OBJECT
public:
    explicit OperatorEditor(const Operator& op, QWidget *parent = nullptr);
    QSize sizeHint() const override;
    void setOperator(const Operator& op) { m_operator = op; }
    Operator getOperator() const { return m_operator; }

signals:
    void operatorData(int mcc, int mnc);

public slots:
    void onOperatorData();

protected:
    void paintEvent(QPaintEvent *event) override;
    bool eventFilter(QObject *watched, QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    Operator m_operator;
    OperatorDataButton* m_operatorDataButton;
};

#endif // OPERATOREDITOR_HPP
