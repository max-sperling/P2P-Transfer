/************************/
/* Author: Max Sperling */
/************************/

#include "conf/IConf.hpp"
#include "trans/ITrans.hpp"
#include "view/IView.hpp"
#include "conf/ConfFactory.hpp"
#include "trans/TransFactory.hpp"
#include "view/ViewFactory.hpp"

#include <QApplication>
#include <filesystem>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    std::filesystem::path binPath(argv[0]);
    std::filesystem::path confPath = binPath.parent_path() / std::string("conf/config.json");

    QApplication app(argc, argv);

    conf::IConfSPtr conf = conf::ConfFactory::create(conf::ConfType::Json);
    trans::ITransSPtr trans = trans::TransFactory::create(trans::TransType::P2P);
    view::IViewSPtr view = view::ViewFactory::create(view::ViewType::Qute);

    view->start();

    auto conDetails = make_shared<conf::ConnectionDetails>();
    if (!conf->read(confPath, *conDetails))
    {
        view->logIt("Error while reading Config");
    }

    if (!trans->init(view)) return 2;
    if (!trans->exec(conDetails)) return 3;

    app.exec();

    return 0;
}
