#include "TreeItemTypes.hpp"

#include <QPainter>
#include <QApplication>
#include <QIcon>
#include <QPalette>

static constexpr QSize iconSize(16, 16);
static constexpr int spaceSize = 4;

void Operator::paint(QPainter *painter, const QRect &rect, const QPalette &palette) const
{
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);

    auto fileName = iconFileName();
    QIcon icon(fileName);

    icon.paint(painter, rect, Qt::AlignLeft);

    auto text = QString("%1 (%2, %3)").arg(name).arg(mcc).arg(mnc);
    QPen textPen;
    QRect textOffset(
        rect.left() + iconSize.width() + spaceSize, rect.top(),
        rect.width() - iconSize.width() - spaceSize, rect.height()
    );

    textPen.setBrush(palette.windowText());
    painter->setPen(textPen);
    painter->drawText(textOffset, Qt::AlignLeft, text);
    painter->restore();
}

QSize Operator::sizeHint() const
{
    const auto mccLength = QString::number(mcc).length();
    const auto mncLength = QString::number(mnc).length();

    // '5' - is number of separators in operator tree item text
    return iconSize + QSize((name.length() + mccLength + mncLength + 5)
                             * QApplication::font().pointSize(), 0
                            );
}

QString Operator::iconFileName() const
{
    return QString(":/Icons/Operators/%1_%2.png").arg(mcc).arg(mnc);
}

void Country::paint(QPainter *painter, const QRect &rect, const QPalette &palette) const
{
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);

    auto fileName = iconFileName();
    QIcon icon(fileName);

    icon.paint(painter, rect, Qt::AlignLeft);

    QPen textPen;
    QFont font = painter->font();
    QRect textOffset(
        rect.left() + iconSize.width() + spaceSize, rect.top(),
        rect.width() - iconSize.width() - spaceSize, rect.height()
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
    return iconSize
           + QSize(name.length() * QApplication::font().pixelSize(), 0);
}

QString Country::iconFileName() const
{
    return QString(":/Icons/Countries/%1.png").arg(code);
}
