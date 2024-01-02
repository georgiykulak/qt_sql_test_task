#ifndef TREEITEMTYPES_H
#define TREEITEMTYPES_H

#include <QString>
#include <QMetaType>

#include <vector>
#include <map>

class QPainter;

struct Operator
{
    QString name;
    int mnc;
    int mcc;

    void paint(QPainter* painter,
               const QRect& rect,
               const QPalette &palette) const;
    QSize sizeHint() const;
    QString iconFileName() const;
};
Q_DECLARE_METATYPE(Operator);
const int kOperatorMetaId = qRegisterMetaType<Operator>();

using Operators = std::vector<Operator>;

struct Country
{
    QString name;
    QString code;
    int mcc;

    void paint(QPainter* painter,
               const QRect& rect,
               const QPalette &palette) const;
    QSize sizeHint() const;
    QString iconFileName() const;
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
