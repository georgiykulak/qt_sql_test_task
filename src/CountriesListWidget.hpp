#ifndef COUNTRIESLISTWIDGET_HPP
#define COUNTRIESLISTWIDGET_HPP

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class CountriesListWidget;
}
QT_END_NAMESPACE

class CountriesListWidget : public QWidget
{
    Q_OBJECT

public:
    CountriesListWidget(QWidget *parent = nullptr);
    ~CountriesListWidget();

private:
    Ui::CountriesListWidget *ui;
};
#endif // COUNTRIESLISTWIDGET_HPP
