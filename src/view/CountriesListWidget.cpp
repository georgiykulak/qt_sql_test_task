#include "CountriesListWidget.hpp"
#include <model/CountriesOperatorsModel.hpp>
#include <model/TreeIconTextDelegate.hpp>
#include <view/buttons/AddOperatorButton.hpp>
#include "ui_CountriesListWidget.h"

#include <QHBoxLayout>
#include <QTreeView>
#include <QTreeWidget>
#include <QGraphicsAnchorLayout>

CountriesListWidget::CountriesListWidget(
    std::shared_ptr<CountriesOperatorsModel> model,
    QWidget *parent)
    : QTreeView(parent)
    , ui(new Ui::CountriesListWidget)
{
    ui->setupUi(this);

    setModel(model.get());

    setWindowTitle("Countries and operators");
    setMinimumSize(500, 350);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setHeaderHidden(true);
    setItemDelegate(new TreeIconTextDelegate(model));
    setEditTriggers(QAbstractItemView::EditTrigger::AllEditTriggers);
    setMouseTracking(true);
    connect(this, &CountriesListWidget::entered,
            this, &CountriesListWidget::openPersistentEditor);

    QHBoxLayout* layout = new QHBoxLayout;
    setLayout(layout);

    m_operatorDataButton = new AddOperatorButton(model, this);
    m_operatorDataButton->move(size().width() - 50, size().height() - 50);
    m_operatorDataButton->show();
    m_operatorDataButton->setVisible(true);
}

CountriesListWidget::~CountriesListWidget()
{
    delete ui;
}

void CountriesListWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);

    m_operatorDataButton->move(size().width() - 50, size().height() - 40);
}
