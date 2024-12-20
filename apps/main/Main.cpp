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

    QApplication app(argc, argv);

    auto conf = conf::ConfFactory::create(conf::ConfType::Json);
    auto trans = trans::TransFactory::create(trans::TransType::P2P);
    auto view = view::ViewFactory::create(view::ViewType::Qute);

    view->exec();
    conf::IConDetSPtr conDet = make_shared<conf::ConnectionDetails>();
    if (!conf->read(view, confPath, *conDet)) { view->logIt("Reading config failed"); }
    if (!trans->exec(view, conDet)) { view->logIt("Setup transport failed"); }

    view->attach(&*trans);
    app.exec();
    view->detach(&*trans);

    return 0;
}
