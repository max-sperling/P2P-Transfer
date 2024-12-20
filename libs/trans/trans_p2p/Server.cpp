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
    Server::Server(const view::ILoggerSPtr& log, const shared_ptr<conf::ConnectionDetails>& det, const shared_ptr<IConLisVec>& lis)
    {
        m_log = log;
        m_conDet = det;
        m_conLis = lis;
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
        auto* input = new Input(m_log, m_conDet, m_conLis, socketId);
        connect(input, SIGNAL(finished()), input, SLOT(deleteLater()));
        input->start();
    }
    // ****************************************************************************************************************
}
