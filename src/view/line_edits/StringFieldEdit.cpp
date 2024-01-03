#include "StringFieldEdit.hpp"

#include <QLineEdit>

StringFieldEdit::StringFieldEdit(const QColor& bg,
                                 QWidget* parent)
    : IFieldEdit{bg, parent}
{
    enableClearButton();
}

void StringFieldEdit::onTextChanged(const QString& newText)
{
    if (newText.isEmpty())
    {
        setValid(false);
    }
    else
    {
        setValid(true);
        emit textChangedAndValid(newText);
    }
}
