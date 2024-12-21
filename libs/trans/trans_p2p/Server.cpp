/************************/
/* Author: Max Sperling */
/************************/

#include "trans/trans_p2p/Server.hpp"

#include "conf/IConf.hpp"
#include "trans/trans_p2p/Input.hpp"

#include <QHostAddress>

using namespace std;

namespace trans::trans_p2p
{
    // ***** Public ***************************************************************************************************
    Server::Server(const view::ILoggerSPtr& log, const shared_ptr<conf::ConnectionDetails>& det, ISerLisVec& lis)
    : m_serLis(lis)
    {
        m_logger = log;
        m_conDet = det;
    }

    bool Server::init()
    {
        if (!listen(QHostAddress::Any, m_conDet->m_port)) { return false; }

        return true;
    }
    // ****************************************************************************************************************

    // ***** Protected ************************************************************************************************
    void Server::incomingConnection(qintptr socketId)
    {
        auto* input = new Input(m_logger, m_conDet, m_serLis, socketId);
        connect(input, SIGNAL(finished()), input, SLOT(deleteLater()));
        input->start();
    }
    // ****************************************************************************************************************
}
