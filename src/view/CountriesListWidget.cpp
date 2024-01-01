#include "CountriesListWidget.hpp"
#include <model/TreeIconTextDelegate.hpp>
#include <view/buttons/OperatorDataButton.hpp>
#include "ui_CountriesListWidget.h"

#include <QHBoxLayout>
#include <QTreeView>
#include <QTreeWidget>
#include <QGraphicsAnchorLayout>

CountriesListWidget::CountriesListWidget(QWidget *parent)
    : QTreeView(parent)
    , ui(new Ui::CountriesListWidget)
{
    ui->setupUi(this);
    setWindowTitle("Countries and operators");

    QHBoxLayout* layout = new QHBoxLayout;
    setLayout(layout);

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setEditTriggers(QAbstractItemView::EditTrigger::AllEditTriggers);
    setMouseTracking(true);
    connect(this, &CountriesListWidget::entered,
            this, &CountriesListWidget::openPersistentEditor);

    setHeaderHidden(true);
    setItemDelegate(new TreeIconTextDelegate);

    OperatorDataButton* operatorDataButton = new OperatorDataButton(this);
    operatorDataButton->move(size().width() - 35, size().height() - 35);
    operatorDataButton->show();
}

CountriesListWidget::~CountriesListWidget()
{
    delete ui;
}
