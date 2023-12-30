#include "OperatorEditorDialog.hpp"

OperatorEditorDialog::OperatorEditorDialog(QAbstractItemModel* model,
                                           QWidget *parent)
    : QDialog{parent}
{
    m_model = model;
}
