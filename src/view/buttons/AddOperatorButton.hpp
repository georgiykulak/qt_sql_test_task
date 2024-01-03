#ifndef ADDOPERATORBUTTON_HPP
#define ADDOPERATORBUTTON_HPP

#include <QWidget>

class CountriesOperatorsModel;

class AddOperatorButton : public QWidget
{
    Q_OBJECT
public:
    explicit AddOperatorButton(std::shared_ptr<CountriesOperatorsModel> model,
                               QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    std::shared_ptr<CountriesOperatorsModel> m_model;
};

#endif // ADDOPERATORBUTTON_HPP
