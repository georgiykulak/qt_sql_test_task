#include "OperatorEditorDialog.hpp"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QAction>

OperatorEditorDialog::OperatorEditorDialog(QAbstractItemModel* model,
                                           QWidget *parent)
    : QDialog{parent}
{
    m_model = model;

    setMinimumSize(300, 200);
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_DeleteOnClose);

    InitLayouts();
}

void OperatorEditorDialog::InitLayouts()
{
    QVBoxLayout* dialogLayout = new QVBoxLayout;
    QHBoxLayout* widgetNameLayout = new QHBoxLayout;
    QGridLayout* operatorDataLayout = new QGridLayout;
    QHBoxLayout* buttonLayout = new QHBoxLayout;

    AddHeaderTo(widgetNameLayout);
    AddNameEditorTo(operatorDataLayout);
    AddMccEditorTo(operatorDataLayout);
    AddMncEditorTo(operatorDataLayout);
    AddSaveCancelTo(buttonLayout);

    dialogLayout->addLayout(widgetNameLayout);
    dialogLayout->addLayout(operatorDataLayout);

    QSpacerItem *vSpacer
        = new QSpacerItem(1, 1, QSizePolicy::Fixed, QSizePolicy::Expanding);
    dialogLayout->addSpacerItem(vSpacer);
    dialogLayout->addLayout(buttonLayout);

    setLayout(dialogLayout);
}

void OperatorEditorDialog::AddHeaderTo(QHBoxLayout *layout)
{
    QLabel* labelWidgetName = new QLabel(this);
    QFont font = labelWidgetName->font();
    font.setBold(true);
    labelWidgetName->setFont(font);
    labelWidgetName->setText("Operator editor");
    labelWidgetName->move(width() / 2 - labelWidgetName->width() / 2, 5);
    labelWidgetName->show();

    QLabel* imageOperator = new QLabel(this);
    // TODO: Add method to update image by editing
    QPixmap pixmap(":/Icons/Operators/202_1.png");
    pixmap.setDevicePixelRatio(0.5);
    imageOperator->setPixmap(pixmap);

    layout->addWidget(imageOperator);
}

void OperatorEditorDialog::AddNameEditorTo(QGridLayout *layout)
{
    QLabel* labelName = new QLabel("Name", this);
    // TODO: Add clear button
    // TODO: Set style for the line edit
    QLineEdit* editName = new QLineEdit(this);

    layout->addWidget(labelName, 0, 0);
    layout->addWidget(editName, 0, 1);
}

void OperatorEditorDialog::AddMccEditorTo(QGridLayout *layout)
{
    QLabel* labelMcc = new QLabel("MCC", this);
    // TODO: Set style for the line edit
    QLineEdit* editMcc = new QLineEdit(this);
    QLabel* imageCountry = new QLabel(this);

    // TODO: Add method to update image by editing
    QPixmap pixmap(":/Icons/Countries/AU.png");
    pixmap.setDevicePixelRatio(0.75);
    imageCountry->setPixmap(pixmap);

    QHBoxLayout* hLayout = new QHBoxLayout;
    hLayout->addWidget(editMcc);
    hLayout->addWidget(imageCountry);

    layout->addWidget(labelMcc, 1, 0);
    layout->addLayout(hLayout, 1, 1);
}

void OperatorEditorDialog::AddMncEditorTo(QGridLayout *layout)
{
    QLabel* labelMnc = new QLabel("MNC", this);
    // TODO: Set style for the line edit
    QLineEdit* editMnc = new QLineEdit(this);

    layout->addWidget(labelMnc, 2, 0);
    layout->addWidget(editMnc, 2, 1);
}

void OperatorEditorDialog::AddSaveCancelTo(QHBoxLayout *layout)
{
    QPushButton* buttonSave = new QPushButton("Save", this);
    QPushButton* buttonCancel = new QPushButton("Cancel", this);

    connect(buttonSave, &QPushButton::clicked,
            this, &OperatorEditorDialog::accept);
    connect(buttonCancel, &QPushButton::clicked,
            this, &OperatorEditorDialog::reject);

    QSpacerItem *hSpacer
        = new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Fixed);
    layout->addSpacerItem(hSpacer);
    layout->addWidget(buttonSave);
    layout->addWidget(buttonCancel);
}
