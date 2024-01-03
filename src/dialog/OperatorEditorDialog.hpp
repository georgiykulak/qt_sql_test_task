#ifndef OPERATOREDITORDIALOG_HPP
#define OPERATOREDITORDIALOG_HPP

#include <QDialog>

class CountriesOperatorsModel;
class QGridLayout;
class QHBoxLayout;
class QLabel;
class StringFieldEdit;
class IntFieldEdit;

class OperatorEditorDialog : public QDialog
{
    Q_OBJECT
public:
    explicit OperatorEditorDialog(std::shared_ptr<CountriesOperatorsModel> model,
                                  const QModelIndex* index = nullptr,
                                  QWidget* parent = nullptr);

signals:
    void retrieveCountryCodeByMcc(int mcc, QString& code);

public slots:
    void accept() override;

private:
    std::shared_ptr<CountriesOperatorsModel> m_model;
    const QModelIndex* m_operatorIndex;
    QLabel* m_imageOperator;
    QLabel* m_imageCountry;
    QString m_operatorName;
    int m_operatorMcc;
    int m_operatorMnc;
    bool m_operatorNameValid = false;
    bool m_operatorMccValid = false;
    bool m_operatorMncValid = true;

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
    void setImageCountryByCode(const QString& code);
    void setUpNameLineEdit(StringFieldEdit* editName);
    void setUpMccLineEdit(IntFieldEdit* editMcc);
    void setUpMncLineEdit(IntFieldEdit* editMnc);
};

#endif // OPERATOREDITORDIALOG_HPP
