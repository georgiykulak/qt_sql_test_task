#include "TreeItemTypes.hpp"

#include <QPainter>
#include <QApplication>
#include <QIcon>
#include <QPalette>

void Operator::paint(QPainter *painter, const QRect &rect, const QPalette &palette) const
{
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);

    auto fileName = iconFileName(mcc, mnc);
    QIcon icon(fileName);

    icon.paint(painter, rect, Qt::AlignLeft);

    QPen textPen;
    QRect textOffset(
        rect.left() + iconSize.first + spaceSize, rect.top(),
        rect.width() - iconSize.first - spaceSize, rect.height()
    );

    textPen.setBrush(palette.windowText());
    painter->setPen(textPen);
    painter->drawText(textOffset, Qt::AlignLeft, text());
    painter->restore();
}

QSize Operator::sizeHint() const
{
    const auto mccLength = QString::number(mcc).length();
    const auto mncLength = QString::number(mnc).length();

    // '5' - is number of separators in operator tree item text
    return QSize(iconSize.first, iconSize.second)
          + QSize((name.length() + mccLength + mncLength + 5)
                  * QApplication::font().pointSize(), 0);
}

QString Operator::text() const
{
    return QString("%1 (%2, %3)").arg(name).arg(mcc).arg(mnc);
}

QString Operator::iconFileName(int mcc, int mnc)
{
    return QString(":/Icons/Operators/%1_%2.png").arg(mcc).arg(mnc);
}

void Country::paint(QPainter *painter, const QRect &rect, const QPalette &palette) const
{
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);

    auto fileName = iconFileName(code);
    QIcon icon(fileName);

    icon.paint(painter, rect, Qt::AlignLeft);

    QPen textPen;
    QFont font = painter->font();
    QRect textOffset(
        rect.left() + iconSize.first + spaceSize, rect.top(),
        rect.width() - iconSize.first - spaceSize, rect.height()
    );

    font.setBold(true);
    painter->setFont(font);
    textPen.setBrush(palette.windowText());
    painter->setPen(textPen);
    painter->drawText(textOffset, Qt::AlignLeft, name);
    painter->restore();
}

QSize Country::sizeHint() const
{
    return QSize(iconSize.first, iconSize.second)
           + QSize(name.length() * QApplication::font().pixelSize(), 0);
}

QString Country::iconFileName(const QString& code)
{
    return QString(":/Icons/Countries/%1.png").arg(code);
}
