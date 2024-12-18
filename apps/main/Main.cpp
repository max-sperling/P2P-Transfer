/************************/
/* Author: Max Sperling */
/************************/

#include "conf/ConfFactory.hpp"
#include "conf/IConf.hpp"
#include "trans/ITrans.hpp"
#include "trans/TransFactory.hpp"
#include "view/IView.hpp"
#include "view/ViewFactory.hpp"

#include <QApplication>

#include <filesystem>

using namespace std;

int main(int argc, char *argv[])
{
    std::filesystem::path binPath(argv[0]);
    std::filesystem::path confPath = binPath.parent_path() / std::string("conf/config.json");
    conf::IConDetSPtr conDet = make_shared<conf::ConnectionDetails>();

    QApplication app(argc, argv);

    conf::IConfSPtr conf = conf::ConfFactory::create(conf::ConfType::Json);
    trans::ITransSPtr trans = trans::TransFactory::create(trans::TransType::P2P);
    view::IViewSPtr view = view::ViewFactory::create(view::ViewType::Qute);

    view->exec();
    if (!conf->read(view, confPath, *conDet)) { view->logIt("Reading config failed"); }
    if (!trans->exec(view, conDet)) { view->logIt("Setup transport failed"); }

    app.exec();

    return 0;
}
