#include "OperatorEditorDialog.hpp"
#include <model/CountriesOperatorsModel.hpp>
#include <view/line_edits/IntFieldEdit.hpp>
#include <view/line_edits/StringFieldEdit.hpp>

#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QAbstractItemModel>
#include <QMessageBox>

OperatorEditorDialog::OperatorEditorDialog(
    const std::shared_ptr<CountriesOperatorsModel>& model,
    const QModelIndex* index,
    QWidget *parent)
    : QDialog{parent}
    , m_model{model}
    , m_operatorIndex{index}
{
    setMinimumSize(300, 200);
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_DeleteOnClose);
    setModal(true);

    InitLayouts();
}

void OperatorEditorDialog::accept()
{
    if (m_operatorIndex)
    {
        Operator op = qvariant_cast<Operator>(m_operatorIndex->data());
        op.name = m_operatorName;

        QVariant oper(kOperatorMetaId, &op);
        m_model->setData(*m_operatorIndex, oper);

        QDialog::accept();
    }
    else if (m_operatorNameValid && m_operatorMccValid && m_operatorMncValid)
    {
        Operator op;
        op.name = m_operatorName;
        op.mcc = m_operatorMcc;
        op.mnc = m_operatorMnc;

        QVariant oper(kOperatorMetaId, &op);
        m_model->setData(QModelIndex(), oper, InsertRole);

        QDialog::accept();
    }
    else
    {
        QStringList invalidFields;
        if (!m_operatorNameValid) invalidFields << "name";
        if (!m_operatorMccValid) invalidFields << "mcc";
        if (!m_operatorMncValid) invalidFields << "mnc";

        QMessageBox::information(
            this, tr("Invalid operator!"),
            tr(invalidFields.size() > 1 ? "Those fields are" : "This field is")
            + tr(" invalid: ") + invalidFields.join(", ") +
            tr(".\nPlease enter valid information and try again."),
            QMessageBox::Ok
        );
    }
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
    QColor background = palette().color(QPalette::Window);
    StringFieldEdit* editName = new StringFieldEdit(background, this);

    setUpNameLineEdit(editName);

    layout->addWidget(labelName, 0, 0);
    layout->addWidget(editName, 0, 1);
}

void OperatorEditorDialog::AddMccEditorTo(QGridLayout *layout)
{
    QLabel* labelMcc = new QLabel("MCC", this);
    QColor background = palette().color(QPalette::Window);
    IntFieldEdit* editMcc = new IntFieldEdit(background, this);

    m_imageCountry = new QLabel(this);
    updateImageCountry();

    setUpMccLineEdit(editMcc);

    QHBoxLayout* hLayout = new QHBoxLayout;
    hLayout->addWidget(editMcc);
    hLayout->addWidget(m_imageCountry);

    layout->addWidget(labelMcc, 1, 0);
    layout->addLayout(hLayout, 1, 1);
}

void OperatorEditorDialog::AddMncEditorTo(QGridLayout *layout)
{
    QLabel* labelMnc = new QLabel("MNC", this);
    QColor background = palette().color(QPalette::Window);
    IntFieldEdit* editMnc = new IntFieldEdit(background, this);

    setUpMncLineEdit(editMnc);

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

        setImageOperator(oper.mcc, oper.mnc);
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

        setImageCountry(country.code);
    }
    else
    {
        drawBadImageCountry();
    }
}

void OperatorEditorDialog::setImageCountry(const QString& code)
{
    auto fileName = Country::IconFileName(code);
    QPixmap pixmap(fileName);
    pixmap.setDevicePixelRatio(0.75);
    m_imageCountry->setPixmap(pixmap);
}

bool OperatorEditorDialog::setImageOperator(int mcc, int mnc)
{
    auto fileName = Operator::IconFileName(mcc, mnc);
    QPixmap pixmap;
    if (!pixmap.load(fileName))
        return false;

    pixmap.setDevicePixelRatio(0.5);
    m_imageOperator->setPixmap(pixmap);

    return true;
}

void OperatorEditorDialog::setUpNameLineEdit(StringFieldEdit* editName)
{
    if (m_operatorIndex)
    {
        Operator oper = qvariant_cast<Operator>(m_operatorIndex->data());
        editName->setText(oper.name);
        m_operatorName = oper.name;
        m_operatorNameValid = true;
    }
    else
    {
        editName->setValid(false);
    }

    connect(editName, &StringFieldEdit::textChangedAndValid,
            this, [this](const QString& text) { m_operatorName = text; });
    connect(editName, &StringFieldEdit::validStateChanged,
            this, [this](bool valid){ m_operatorNameValid = valid; });
}

void OperatorEditorDialog::setUpMccLineEdit(IntFieldEdit* editMcc)
{
    if (m_operatorIndex)
    {
        Operator oper = qvariant_cast<Operator>(m_operatorIndex->data());
        editMcc->setText(QString::number(oper.mcc));
        editMcc->setDisabled();
        m_operatorMcc = oper.mcc;
        m_operatorMccValid = true;
    }
    else
    {
        editMcc->setText("0");
        editMcc->setValid(false);

        connect(editMcc, &IntFieldEdit::numberChangedAndValid,
                this, [this, editMcc](int mcc)
                {
                    QString code;
                    emit retrieveCountryCodeByMcc(mcc, code);

                    if (code.isEmpty())
                    {
                        editMcc->setValid(false);
                        drawBadImageCountry();
                        drawBadImageOperator();
                        return;
                    }

                    editMcc->setValid(true);
                    setImageCountry(code);
                    if (!setImageOperator(mcc, m_operatorMnc))
                        drawBadImageOperator();

                    m_operatorMcc = mcc;
                });
        connect(editMcc, &IntFieldEdit::validStateChanged,
                this, [this](bool valid){ m_operatorMccValid = valid; });
    }
}

void OperatorEditorDialog::setUpMncLineEdit(IntFieldEdit* editMnc)
{
    if (m_operatorIndex)
    {
        Operator oper = qvariant_cast<Operator>(m_operatorIndex->data());
        editMnc->setText(QString::number(oper.mnc));
        editMnc->setDisabled();
        m_operatorMnc = oper.mnc;
        m_operatorMncValid = true;
    }
    else
    {
        editMnc->setText("0");

        connect(editMnc, &IntFieldEdit::numberChangedAndValid,
                this, [this](int mnc)
                {
                    if (!setImageOperator(m_operatorMcc, mnc))
                        drawBadImageOperator();

                    m_operatorMnc = mnc;
                });
        connect(editMnc, &IntFieldEdit::validStateChanged,
                this, [this](bool valid){ m_operatorMncValid = valid; });
    }
}
