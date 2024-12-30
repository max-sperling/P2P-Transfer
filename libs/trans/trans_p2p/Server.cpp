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
        QThread* thread = new QThread;
        Input* input = new Input(m_logger, m_conDet, m_serLis, socketId);

        input->moveToThread(thread);

        connect(thread, SIGNAL(started()), input, SLOT(start()));
        connect(input, SIGNAL(finished()), thread, SLOT(quit()));

        connect(input, SIGNAL(finished()), input, SLOT(deleteLater()));
        connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

        thread->start();
    }
    // ****************************************************************************************************************
}
