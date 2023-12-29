#include "CountriesListWidget.hpp"
#include "ui_CountriesListWidget.h"

CountriesListWidget::CountriesListWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CountriesListWidget)
{
    ui->setupUi(this);
}

CountriesListWidget::~CountriesListWidget()
{
    delete ui;
}
