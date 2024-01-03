#ifndef FIELDEDIT_HPP
#define FIELDEDIT_HPP

#include <QWidget>

class QLineEdit;

class IFieldEdit : public QWidget
{
    Q_OBJECT
public:
    explicit IFieldEdit(const QColor& bg,
                        QWidget* parent = nullptr);

    QSize sizeHint() const override;
    void setDisabled();
    void setText(const QString& text);
    void setValid(bool valid);

signals:
    void validStateChanged(bool valid);

protected:
    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;
    void enableClearButton();

protected slots:
    virtual void onTextChanged(const QString& newText) = 0;

private:
    static constexpr QSize m_margin = QSize(4, 4);

    QLineEdit* m_lineEdit;
    bool m_valid = true;

    void drawValidityFrame(QPainter& painter) const;
};

#endif // FIELDEDIT_HPP
