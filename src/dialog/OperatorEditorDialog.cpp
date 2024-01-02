#include "OperatorEditorDialog.hpp"
#include <model/TreeItemTypes.hpp>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QPixmap>
#include <QPainter>
#include <QAbstractItemModel>

OperatorEditorDialog::OperatorEditorDialog(
    std::shared_ptr<QAbstractItemModel> model,
    const QModelIndex* index,
    QWidget *parent)
    : QDialog{parent}
    , m_model{model}
    , m_operatorIndex{index}
{
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

    m_imageOperator = new QLabel(this);
    updateImageOperator();

    layout->addWidget(m_imageOperator);
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

    m_imageCountry = new QLabel(this);
    updateImageCountry();

    QHBoxLayout* hLayout = new QHBoxLayout;
    hLayout->addWidget(editMcc);
    hLayout->addWidget(m_imageCountry);

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

void OperatorEditorDialog::drawQuestionMark(QLabel* source,
                                            qreal width,
                                            int pixSize)
{
    QPixmap pixmap(width, width);
    QPainter painter(&pixmap);

    QFont font(QFont("Courier"));
    font.setBold(true);
    font.setPixelSize(pixSize);
    painter.setFont(font);
    QPen pen;
    pen.setColor(Qt::black);
    pen.setBrush(Qt::black);
    painter.setPen(pen);

    painter.fillRect(rect(), palette().color(QPalette::Window));
    painter.drawText(0, width - 1, "?");

    source->setPixmap(pixmap);
}

void OperatorEditorDialog::drawBadImageOperator()
{
    // Values were chosen for 'Courier' font
    constexpr qreal width = 32;
    constexpr int pixSize = 53;
    drawQuestionMark(m_imageOperator, width, pixSize);
}

void OperatorEditorDialog::drawBadImageCountry()
{
    // Values were chosen for 'Courier' font
    constexpr qreal width = 20;
    constexpr int pixSize = 32;
    drawQuestionMark(m_imageCountry, width, pixSize);
}

void OperatorEditorDialog::updateImageOperator()
{
    if (m_operatorIndex)
    {
        Operator oper = qvariant_cast<Operator>(m_operatorIndex->data());
        auto fileName = oper.iconFileName();
        QPixmap pixmap(fileName);
        pixmap.setDevicePixelRatio(0.5);
        m_imageOperator->setPixmap(pixmap);
    }
    else
    {
        drawBadImageOperator();
    }
}

void OperatorEditorDialog::updateImageCountry()
{
    if (m_operatorIndex)
    {
        QModelIndex countryIndex = m_model->parent(*m_operatorIndex);
        Country country = qvariant_cast<Country>(countryIndex.data());

        auto fileName = country.iconFileName();
        QPixmap pixmap(fileName);
        pixmap.setDevicePixelRatio(0.75);
        m_imageCountry->setPixmap(pixmap);
    }
    else
    {
        drawBadImageCountry();
    }
}
