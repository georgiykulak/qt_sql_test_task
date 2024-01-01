#include <view/CountriesListWidget.hpp>
#include <model/CountriesOperatorsModel.hpp>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CountriesListWidget view;
    std::shared_ptr<CountriesOperatorsModel> model
        = std::make_shared<CountriesOperatorsModel>("system.db");

    view.setModel(model.get());
    model->DownloadSync();
    view.show();

    return a.exec();
}
