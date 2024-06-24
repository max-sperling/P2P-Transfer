/************************/
/* Author: Max Sperling */
/************************/

#include "TransferApp.hpp"
#include "view/ViewFactory.hpp"
#include "conf/ConfFactory.hpp"
#include "trans/TransFactory.hpp"
#include "trans/ITrans.hpp"
#include <QApplication>

TransferApp::TransferApp(const view::ViewType viewType, const conf::ConfType confType, const trans::TransType transType)
    : m_viewType(viewType), m_confType(confType), m_transType(transType) {}

bool TransferApp::exec(int argc, char *argv[])
{
    QApplication app(argc, argv);

    view::IViewSPtr view = view::ViewFactory::create(m_viewType);
    conf::IConfSPtr conf = conf::ConfFactory::create(m_confType);
    trans::ITransSPtr trans = trans::TransFactory::create(m_transType);

    if(!trans->init(view, conf)) return false;
    if(!trans->exec()) return false;

    app.exec();

    return true;
}