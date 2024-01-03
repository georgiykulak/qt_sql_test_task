#ifndef OPERATOREDITOR_HPP
#define OPERATOREDITOR_HPP

#include <model/TreeItemTypes.hpp>

#include <QWidget>

class CountriesOperatorsModel;
class OperatorDataButton;

class OperatorEditor : public QWidget
{
    Q_OBJECT
public:
    explicit OperatorEditor(std::shared_ptr<CountriesOperatorsModel> model,
                            const QModelIndex* index,
                            QWidget *parent = nullptr);
    QSize sizeHint() const override;
    void setOperator(const Operator& op);
    Operator getOperator() const;

signals:
    void operatorData(int mcc, int mnc);

public slots:
    void OnOperatorData();

protected:
    void paintEvent(QPaintEvent *event) override;
    bool eventFilter(QObject *watched, QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    std::shared_ptr<CountriesOperatorsModel> m_rootModel;
    const QModelIndex* m_index;
    OperatorDataButton* m_operatorDataButton;
};

#endif // OPERATOREDITOR_HPP
