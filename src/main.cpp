#include "CountriesListWidget.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CountriesListWidget w;
    w.show();
    return a.exec();
}
