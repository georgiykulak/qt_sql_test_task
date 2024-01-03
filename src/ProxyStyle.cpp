#include "ProxyStyle.hpp"

QIcon ProxyStyle::standardIcon(StandardPixmap standardIcon,
                               const QStyleOption *option,
                               const QWidget *widget) const
{
    if (standardIcon == QStyle::SP_LineEditClearButton)
        return QIcon(drawButtonPixmap());

    return QProxyStyle::standardIcon(standardIcon, option, widget);
}

QPixmap ProxyStyle::drawButtonPixmap() const
{
    int width = 20;
    int margin = 4;
    QPixmap pixmap(width, width);
    pixmap.fill(QColor(Qt::transparent));
    QPainter painter(&pixmap);

    QLine lineLTopRBottom(margin, margin, width - margin, width - margin);
    QLine lineRTopLBottom(width - margin, margin, margin, width - margin);

    QPen mPen;
    mPen.setWidth(1);
    mPen.setBrush(Qt::black);
    painter.setPen(mPen);

    painter.drawLine(lineLTopRBottom);
    painter.drawLine(lineRTopLBottom);

    return pixmap;
}
