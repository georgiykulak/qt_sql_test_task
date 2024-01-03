#ifndef TREEITEMTYPES_H
#define TREEITEMTYPES_H

#include <QString>
#include <QMetaType>

#include <vector>
#include <map>

class QPainter;

enum CustomItemDataRole
{
    InsertRole = Qt::UserRole + 1
};

constexpr std::pair<int, int> iconSize(16, 16);
constexpr int spaceSize = 4;

struct Operator
{
    QString name;
    int mnc;
    int mcc;

    void Paint(QPainter* painter,
               const QRect& rect,
               const QPalette &palette) const;
    QSize SizeHint() const;
    QString Text() const;

    static QString IconFileName(int mcc, int mnc);
};
Q_DECLARE_METATYPE(Operator);
const int kOperatorMetaId = qRegisterMetaType<Operator>();

using Operators = std::vector<Operator>;

struct Country
{
    QString name;
    QString code;
    int mcc;

    void Paint(QPainter* painter,
               const QRect& rect,
               const QPalette &palette) const;
    QSize SizeHint() const;

    static QString IconFileName(const QString& code);
};
Q_DECLARE_METATYPE(Country);
const int kCountryMetaId = qRegisterMetaType<Country>();

struct CountryData
{
    Country country;
    Operators operators;
};

using Countries = std::map<int, CountryData>;

#endif // TREEITEMTYPES_H
