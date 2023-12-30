#include "TreeItemTypes.h"

#include <QPainter>
#include <QApplication>
#include <QIcon>
#include <QPalette>

static constexpr QSize countryFlagIconSize(16, 16);
static constexpr int countrySpaceSize = 4;

void Operator::paint(QPainter *painter, const QRect &rect, const QPalette &palette) const
{

}

QSize Operator::sizeHint() const
{
    return QSize(name.length() * QApplication::font().pixelSize(), 16); // TODO: change it
}

void Country::paint(QPainter *painter, const QRect &rect, const QPalette &palette) const
{
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);

    auto fileName = QString(":/res/Countries/%1.png").arg(code);
    QIcon icon(fileName);

    icon.paint(painter, rect, Qt::AlignLeft);

    QPen textPen;
    QFont font = painter->font();
    QRect textOffset(
        rect.left() + countryFlagIconSize.width() + countrySpaceSize,
        rect.top(),
        rect.width() - countryFlagIconSize.width() - countrySpaceSize,
        rect.height()
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
    return countryFlagIconSize
           + QSize(name.length() * QApplication::font().pixelSize(), 0);
}
