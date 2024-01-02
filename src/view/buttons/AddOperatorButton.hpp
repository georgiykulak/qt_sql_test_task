#ifndef ADDOPERATORBUTTON_HPP
#define ADDOPERATORBUTTON_HPP

#include <QWidget>

class QAbstractItemModel;

class AddOperatorButton : public QWidget
{
    Q_OBJECT
public:
    explicit AddOperatorButton(std::shared_ptr<QAbstractItemModel> model,
                               QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    std::shared_ptr<QAbstractItemModel> m_model;
};

#endif // ADDOPERATORBUTTON_HPP
