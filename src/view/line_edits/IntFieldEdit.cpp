#include "IntFieldEdit.hpp"

IntFieldEdit::IntFieldEdit(const QColor& bg,
                           QWidget *parent)
    : IFieldEdit{bg, parent}
{}

void IntFieldEdit::onTextChanged(const QString &newText)
{
    bool ok;
    int newNumber = newText.toInt(&ok);

    if (ok)
    {
        setValid(true);
        emit numberChangedAndValid(newNumber);
    }
    else
    {
        setValid(false);
    }
}
