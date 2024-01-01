#ifndef ADDOPERATORBUTTON_HPP
#define ADDOPERATORBUTTON_HPP

#include <QWidget>

class AddOperatorButton : public QWidget
{
    Q_OBJECT
public:
    explicit AddOperatorButton(QWidget *parent = nullptr);

    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

signals:
    void operatorData();
};

#endif // ADDOPERATORBUTTON_HPP
