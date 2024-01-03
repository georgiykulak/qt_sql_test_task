#include "TreeItemTypes.hpp"

#include <QPainter>
#include <QApplication>
#include <QIcon>
#include <QPalette>

void Operator::Paint(QPainter *painter, const QRect &rect, const QPalette &palette) const
{
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);

    auto fileName = IconFileName(mcc, mnc);
    QIcon icon(fileName);

    icon.paint(painter, rect, Qt::AlignLeft);

    QPen textPen;
    QRect textOffset(
        rect.left() + iconSize.first + spaceSize, rect.top(),
        rect.width() - iconSize.first - spaceSize, rect.height()
    );

    textPen.setBrush(palette.windowText());
    painter->setPen(textPen);
    painter->drawText(textOffset, Qt::AlignLeft, Text());
    painter->restore();
}

QSize Operator::SizeHint() const
{
    const auto mccLength = QString::number(mcc).length();
    const auto mncLength = QString::number(mnc).length();

    // '5' - is number of separators in operator tree item text
    return QSize(iconSize.first, iconSize.second)
          + QSize((name.length() + mccLength + mncLength + 5)
                  * QApplication::font().pointSize(), 0);
}

QString Operator::Text() const
{
    return QString("%1 (%2, %3)").arg(name).arg(mcc).arg(mnc);
}

QString Operator::IconFileName(int mcc, int mnc)
{
    return QString(":/Icons/Operators/%1_%2.png").arg(mcc).arg(mnc);
}

void Country::Paint(QPainter *painter, const QRect &rect, const QPalette &palette) const
{
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);

    auto fileName = IconFileName(code);
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

QSize Country::SizeHint() const
{
    return QSize(iconSize.first, iconSize.second)
           + QSize(name.length() * QApplication::font().pixelSize(), 0);
}

QString Country::IconFileName(const QString& code)
{
    return QString(":/Icons/Countries/%1.png").arg(code);
}
