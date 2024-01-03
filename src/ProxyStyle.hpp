#ifndef PROXYSTYLE_HPP
#define PROXYSTYLE_HPP

#include <QProxyStyle>
#include <QPainter>

class ProxyStyle : public QProxyStyle
{
public:
    // Override 'QStyle::SP_LineEditClearButton' with custom drawn icon
    QIcon standardIcon(StandardPixmap standardIcon,
                       const QStyleOption *option = nullptr,
                       const QWidget *widget = nullptr) const override;

private:
    QPixmap drawButtonPixmap() const;
};

#endif // PROXYSTYLE_HPP
