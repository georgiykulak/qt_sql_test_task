#include "CountriesListWidget.hpp"
#include "ui_CountriesListWidget.h"

#include <QHBoxLayout>
#include <QTreeView>
#include <QTreeWidget>
#include <QScrollBar>

CountriesListWidget::CountriesListWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CountriesListWidget)
{
    ui->setupUi(this);

    QHBoxLayout* layout = new QHBoxLayout;
    this->setLayout(layout);

    m_treeView = new QTreeView(this);
    m_treeView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    auto* scrollBar = new QScrollBar(Qt::Orientation::Vertical, this);

    layout->addWidget(m_treeView);
    layout->addWidget(scrollBar);
}

CountriesListWidget::~CountriesListWidget()
{
    delete ui;
}
