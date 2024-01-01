#ifndef OPERATORDATABUTTON_HPP
#define OPERATORDATABUTTON_HPP

#include <QWidget>

class OperatorDataButton : public QWidget
{
    Q_OBJECT
public:
    explicit OperatorDataButton(QWidget *parent = nullptr);

signals:
    void operatorData();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
};

#endif // OPERATORDATABUTTON_HPP
