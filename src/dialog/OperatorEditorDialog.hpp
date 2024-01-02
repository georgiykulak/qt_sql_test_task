#ifndef OPERATOREDITORDIALOG_HPP
#define OPERATOREDITORDIALOG_HPP

#include <QDialog>
#include <QLabel>

class QAbstractItemModel;
class QGridLayout;
class QHBoxLayout;

class OperatorEditorDialog : public QDialog
{
    Q_OBJECT
public:
    explicit OperatorEditorDialog(std::shared_ptr<QAbstractItemModel> model,
                                  const QModelIndex* index = nullptr,
                                  QWidget* parent = nullptr);

private:
    std::shared_ptr<QAbstractItemModel> m_model;
    const QModelIndex* m_operatorIndex;
    QLabel* m_imageOperator;
    QLabel* m_imageCountry;

    void InitLayouts();
    void AddHeaderTo(QHBoxLayout* layout);
    void AddNameEditorTo(QGridLayout* layout);
    void AddMccEditorTo(QGridLayout* layout);
    void AddMncEditorTo(QGridLayout* layout);
    void AddSaveCancelTo(QHBoxLayout* layout);

    void drawQuestionMark(QLabel* source,
                          qreal width,
                          int pixSize);
    void drawBadImageOperator();
    void drawBadImageCountry();
    void updateImageOperator();
    void updateImageCountry();
};

#endif // OPERATOREDITORDIALOG_HPP
