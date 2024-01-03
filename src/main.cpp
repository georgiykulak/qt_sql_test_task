#include <view/CountriesListWidget.hpp>
#include <model/CountriesOperatorsModel.hpp>
#include <ProxyStyle.hpp>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle(new ProxyStyle);

    std::shared_ptr<CountriesOperatorsModel> model
        = std::make_shared<CountriesOperatorsModel>("system.db");
    CountriesListWidget view(model);

    model->DownloadSync();
    view.show();

    return a.exec();
}
