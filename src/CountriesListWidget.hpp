#ifndef COUNTRIESLISTWIDGET_HPP
#define COUNTRIESLISTWIDGET_HPP

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class CountriesListWidget;
}
QT_END_NAMESPACE

class QTreeView;
class CountriesOperatorsModel;
class QAbstractItemDelegate;

class CountriesListWidget : public QWidget
{
    Q_OBJECT

public:
    CountriesListWidget(QWidget *parent = nullptr);
    ~CountriesListWidget();

    void setMyModel(std::shared_ptr<CountriesOperatorsModel> model);

private:
    Ui::CountriesListWidget *ui;
    QTreeView* m_treeView;
};
#endif // COUNTRIESLISTWIDGET_HPP
