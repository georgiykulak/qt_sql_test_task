#include "CountriesListWidget.hpp"
#include "CountriesOperatorsModel.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CountriesListWidget view;
    std::shared_ptr<CountriesOperatorsModel> model
        = std::make_shared<CountriesOperatorsModel>("system.db");
    // TODO: Connect everything in controller class

    model->DownloadSync();
    view.show();

    return a.exec();
}
