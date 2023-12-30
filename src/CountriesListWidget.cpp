#include "CountriesListWidget.hpp"
#include "CountriesOperatorsModel.hpp"
#include "ui_CountriesListWidget.h"

#include <QHBoxLayout>
#include <QTreeView>
#include <QTreeWidget>

CountriesListWidget::CountriesListWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CountriesListWidget)
{
    ui->setupUi(this);

    QHBoxLayout* layout = new QHBoxLayout;
    this->setLayout(layout);

    m_treeView = new QTreeView(this);
    m_treeView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_treeView->setHeaderHidden(true);

    layout->addWidget(m_treeView);
}

CountriesListWidget::~CountriesListWidget()
{
    delete ui;
}

void CountriesListWidget::setMyModel(std::shared_ptr<CountriesOperatorsModel> model)
{
    m_treeView->setModel(model.get());
}
