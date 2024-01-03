#ifndef INTFIELDEDIT_HPP
#define INTFIELDEDIT_HPP

#include "IFieldEdit.hpp"

class IntFieldEdit : public IFieldEdit
{
    Q_OBJECT
public:
    explicit IntFieldEdit(const QColor& bg,
                          QWidget* parent = nullptr);

signals:
    void numberChangedAndValid(int number);

protected slots:
    void onTextChanged(const QString& newText) override;
};

#endif // INTFIELDEDIT_HPP
