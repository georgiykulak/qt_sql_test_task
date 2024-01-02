#ifndef COUNTRIESLISTWIDGET_HPP
#define COUNTRIESLISTWIDGET_HPP

#include <QTreeView>

QT_BEGIN_NAMESPACE
namespace Ui {
class CountriesListWidget;
}
QT_END_NAMESPACE

class CountriesOperatorsModel;
class AddOperatorButton;

class CountriesListWidget : public QTreeView
{
    Q_OBJECT
public:
    CountriesListWidget(std::shared_ptr<QAbstractItemModel> model,
                        QWidget *parent = nullptr);
    ~CountriesListWidget();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    Ui::CountriesListWidget *ui;
    AddOperatorButton* m_operatorDataButton;
};
#endif // COUNTRIESLISTWIDGET_HPP
