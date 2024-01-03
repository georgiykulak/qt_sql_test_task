#ifndef STRINGFIELDEDIT_HPP
#define STRINGFIELDEDIT_HPP

#include "IFieldEdit.hpp"

class StringFieldEdit : public IFieldEdit
{
    Q_OBJECT
public:
    explicit StringFieldEdit(const QColor& bg,
                             QWidget* parent = nullptr);

signals:
    void textChangedAndValid(const QString& text);

protected slots:
    void onTextChanged(const QString& newText) override;
};

#endif // STRINGFIELDEDIT_HPP
