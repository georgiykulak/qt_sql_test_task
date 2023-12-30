#ifndef OPERATOREDITORDIALOG_HPP
#define OPERATOREDITORDIALOG_HPP

#include <QDialog>

class QAbstractItemModel;

class OperatorEditorDialog : public QDialog
{
    Q_OBJECT
public:
    explicit OperatorEditorDialog(QAbstractItemModel* model = nullptr,
                                  QWidget* parent = nullptr);

private:
    QAbstractItemModel* m_model;
};

#endif // OPERATOREDITORDIALOG_HPP
