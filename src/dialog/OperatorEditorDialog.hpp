#ifndef OPERATOREDITORDIALOG_HPP
#define OPERATOREDITORDIALOG_HPP

#include <QDialog>

class QAbstractItemModel;
class QGridLayout;
class QHBoxLayout;

class OperatorEditorDialog : public QDialog
{
    Q_OBJECT
public:
    explicit OperatorEditorDialog(QAbstractItemModel* model = nullptr,
                                  QWidget* parent = nullptr);

private:
    QAbstractItemModel* m_model;
    void InitLayouts();
    void AddHeaderTo(QHBoxLayout* layout);
    void AddNameEditorTo(QGridLayout* layout);
    void AddMccEditorTo(QGridLayout* layout);
    void AddMncEditorTo(QGridLayout* layout);
    void AddSaveCancelTo(QHBoxLayout* layout);
};

#endif // OPERATOREDITORDIALOG_HPP
