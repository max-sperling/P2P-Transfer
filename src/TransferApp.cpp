/************************/
/* Author: Max Sperling */
/************************/

#include "TransferApp.hpp"
#include "view/ViewFactory.hpp"
#include "conf/ConfFactory.hpp"
#include "trans/TransFactory.hpp"
#include "trans/ITrans.hpp"
#include <QApplication>

TransferApp::TransferApp(const ViewType viewType, const ConfType confType,
                         const TransType transType)
    : m_viewType(viewType), m_confType(confType), m_transType(transType) {}

TransferApp::~TransferApp() {}

bool TransferApp::exec(int argc, char *argv[])
{
    QApplication app(argc, argv);

    IViewSPtr view = ViewFactory::create(m_viewType);
    IConfSPtr conf = ConfFactory::create(m_confType);
    ITransSPtr trans = TransFactory::create(m_transType);

    if(!trans->init(view, conf)) return false;
    if(!trans->exec()) return false;

    app.exec();

    return true;
}