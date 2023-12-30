#include "CountriesListWidget.hpp"
#include "TreeIconTextDelegate.hpp"
#include "ui_CountriesListWidget.h"

#include <QHBoxLayout>
#include <QTreeView>
#include <QTreeWidget>

CountriesListWidget::CountriesListWidget(QWidget *parent)
    : QTreeView(parent)
    , ui(new Ui::CountriesListWidget)
{
    ui->setupUi(this);

    QHBoxLayout* layout = new QHBoxLayout;
    setLayout(layout);

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setHeaderHidden(true);
    setItemDelegate(new TreeIconTextDelegate);
}

CountriesListWidget::~CountriesListWidget()
{
    delete ui;
}
