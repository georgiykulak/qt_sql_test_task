#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QMetaType>

#include <vector>
#include <map>

struct Operator
{
    QString name;
    int mnc;
    int mcc;
};
Q_DECLARE_METATYPE(Operator);

using Operators = std::vector<Operator>;

struct Country
{
    QString name;
    QString code;
    int mcc;
};
Q_DECLARE_METATYPE(Country);

struct CountryData
{
    Country country;
    Operators operators;
};

using Countries = std::map<int, CountryData>;

#endif // UTILS_H
