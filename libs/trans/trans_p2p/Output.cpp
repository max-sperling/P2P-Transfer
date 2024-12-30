/************************/
/* Author: Max Sperling */
/************************/

#include "trans/trans_p2p/Output.hpp"

#include "conf/IConf.hpp"
#include "trans/trans_p2p/Streamer.hpp"
#include "trans/trans_p2p/TransP2P.hpp"
#include "view/IView.hpp"

using namespace std;

namespace trans::trans_p2p
{
    // ***** Public ***************************************************************************************************
    Output::Output(const view::ILoggerSPtr& log, const shared_ptr<conf::ConnectionDetails>& det, const vector<string>& items)
    {
        m_logger = log;
        m_conDet = det;
        m_items = items;
        m_logIdent = "[Client]";
        m_socket = nullptr;
        m_socketId = 0;
    }

    Output::~Output() {}
    // ****************************************************************************************************************

    // ***** Public slots *********************************************************************************************
    void Output::start()
    {
        m_socket = new QTcpSocket();
        // m_socket->setSocketOption(QAbstractSocket::SendBufferSizeSocketOption, QVariant::fromValue(max_packet_payload_size));

        connect(m_socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));

        if (!sendItems())
        {
            m_logger->logIt(m_logIdent + " Can't send files");

            cleanupSocket();
            emit finished();
            return;
        }
    }
    // ****************************************************************************************************************

    // ***** Private **************************************************************************************************
    bool Output::sendItems()
    {
        if (!connectToServer()) { return false; }

        m_logger->logIt(m_logIdent + " Start sending files");

        Streamer streamer(m_logger, m_logIdent, m_socket);
        streamer.streamItems(m_items);

        m_logger->logIt(m_logIdent + " Finished sending files");

        if (!disconnectFromServer()) { return false; }

        return true;
    }

    bool Output::connectToServer()
    {
        if (m_socket->state() == QTcpSocket::ConnectedState)
        {
            m_logger->logIt(m_logIdent + " Already connected");
            return true;
        }

        m_socket->connectToHost(QString::fromStdString(m_conDet->m_addr), m_conDet->m_port);

        if (!m_socket->waitForConnected(2000))
        {
            m_logger->logIt(m_logIdent + " Can't connect");
            return false;
        }
        m_logger->logIt(m_logIdent + " Connected");

        m_socketId = m_socket->socketDescriptor();

        return true;
    }

    bool Output::disconnectFromServer()
    {
        if (m_socket->state() == QTcpSocket::UnconnectedState)
        {
            m_logger->logIt(m_logIdent + " Already disconnected");
            return true;
        }

        m_socket->disconnectFromHost();

        if (!m_socket->waitForDisconnected(2000))
        {
            m_logger->logIt(m_logIdent + " Can't disconnect");
            return false;
        }
        m_logger->logIt(m_logIdent + " Disconnected");

        return true;
    }

    void Output::cleanupSocket()
    {
        if (m_socket)
        {
            m_socket->close();
            m_socket->deleteLater();
            m_socket = nullptr;
        }
    }
    // ****************************************************************************************************************

    // ***** Private slots ********************************************************************************************
    void Output::onDisconnected()
    {
        m_logger->logIt(m_logIdent + " Disconnected");

        cleanupSocket();
        emit finished();
    }
    // ****************************************************************************************************************
}
