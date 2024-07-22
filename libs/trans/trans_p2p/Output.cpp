/************************/
/* Author: Max Sperling */
/************************/

#include "trans/trans_p2p/Output.hpp"
#include "trans/trans_p2p/Streamer.hpp"
#include "trans/trans_p2p/TransP2P.hpp"
#include "view/IView.hpp"
#include "conf/IConf.hpp"

#include <QFile>
#include <QFileInfo>

using namespace std;

namespace trans::trans_p2p
{
    // ***** Public ************************************************************************************
    Output::Output(const view::IViewSPtr& view, const shared_ptr<conf::ConnectionDetails>& det,
                   const shared_ptr<IConLisVec>& lis, const vector<string>& items)
    {
        m_view = view;
        m_conDet = det;
        m_conLis = lis;
        m_items = items;
        m_logIdent = "[Client]";
        m_socket = nullptr;
        m_socketId = 0;
    }

    Output::~Output()
    {
        for (IConnectionListener* lis : *m_conLis)
        {
            lis->onConnectionFinished(m_socketId, IConnectionListener::ConnectionType::OUTGOING);
        }
    }
    // *************************************************************************************************

    // ***** Protected *********************************************************************************
    void Output::run()
    {
        m_socket = new QTcpSocket();
        // m_socket->setSocketOption(QAbstractSocket::SendBufferSizeSocketOption, QVariant::fromValue(max_packet_payload_size));

        connect(m_socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));

        if (!sendItems()) return;

        exec();
    }
    // *************************************************************************************************

    // ***** Private ***********************************************************************************
    bool Output::connectToServer()
    {
        if (m_socket->state() == QTcpSocket::ConnectedState)
            return true;

        m_socket->connectToHost(QString::fromStdString(m_conDet->m_addr), m_conDet->m_port);

        if (!m_socket->waitForConnected(2000))
        {
            m_view->logIt(m_logIdent + " Can't connect");
            return false;
        }
        m_view->logIt(m_logIdent + " Connected");

        m_socketId = m_socket->socketDescriptor();

        return true;
    }

    bool Output::disconnectFromServer()
    {
        m_socket->disconnectFromHost();

        if (m_socket->state() != QAbstractSocket::UnconnectedState)
        {
            m_socket->waitForDisconnected(2000);
        }

        return true;
    }

    bool Output::sendItems()
    {
        if (!connectToServer()) return false;

        Streamer streamer(m_view, m_logIdent, m_socket);
        streamer.streamItems(m_items);

        m_socket->waitForBytesWritten(-1);

        if (!disconnectFromServer()) return false;

        return true;
    }
    // *************************************************************************************************

    // ***** Private Slots *****************************************************************************
    void Output::onDisconnected()
    {
        m_view->logIt(m_logIdent + " Disconnected");

        m_socket->close();
        quit();
    }
    // *************************************************************************************************
}
