/************************/
/* Author: Max Sperling */
/************************/

#include "trans/trans_p2p/Server.hpp"
#include "trans/trans_p2p/Income.hpp"
#include "conf/IConf.hpp"
#include <QHostAddress>

using namespace std;

// ***** Public ************************************************************************************
Server::Server(IViewSPtr view, const shared_ptr<ConnectionDetails>& det, const shared_ptr<IConLisVec>& lis)
{
    m_view = view;
    m_conDet = det;
    m_conLis = lis;
}

bool Server::init()
{
    if (!listen(QHostAddress::Any, m_conDet->m_port)) { return false; }

    return true;
}
// *************************************************************************************************

// ***** Protected *********************************************************************************
void Server::incomingConnection(qintptr socketId)
{
    Income *income = new Income(m_view, m_conDet, m_conLis, socketId);
    connect(income, SIGNAL(finished()), income, SLOT(deleteLater()));
    income->start();
}
// *************************************************************************************************
