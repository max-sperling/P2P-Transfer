/************************/
/* Author: Max Sperling */
/************************/

#include "conf/ConfFactory.hpp"
#include "trans/ITrans.hpp"
#include "trans/TransFactory.hpp"
#include "view/ViewFactory.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    conf::IConfSPtr conf = conf::ConfFactory::create(conf::ConfType::Json);
    trans::ITransSPtr trans = trans::TransFactory::create(trans::TransType::P2P);
    view::IViewSPtr view = view::ViewFactory::create(view::ViewType::Qute);

    if (!trans->init(view, conf)) return 1;
    if (!trans->exec()) return 2;

    app.exec();

    return 0;
}
