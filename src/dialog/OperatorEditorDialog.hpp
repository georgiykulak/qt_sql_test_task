#ifndef OPERATOREDITORDIALOG_HPP
#define OPERATOREDITORDIALOG_HPP

#include <QDialog>

class QAbstractItemModel;
class QGridLayout;
class QHBoxLayout;
class QLabel;
class QLineEdit;

class OperatorEditorDialog : public QDialog
{
    Q_OBJECT
public:
    explicit OperatorEditorDialog(std::shared_ptr<QAbstractItemModel> model,
                                  const QModelIndex* index = nullptr,
                                  QWidget* parent = nullptr);

public slots:
    void accept() override;

private:
    std::shared_ptr<QAbstractItemModel> m_model;
    const QModelIndex* m_operatorIndex;
    QLabel* m_imageOperator;
    QLabel* m_imageCountry;
    QString m_operatorName;

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
    void setUpNameLineEdit(QLineEdit* editName);
    void setUpMccLineEdit(QLineEdit* editMcc);
    void setUpMncLineEdit(QLineEdit* editMnc);
};

#endif // OPERATOREDITORDIALOG_HPP
