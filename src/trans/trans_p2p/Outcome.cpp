/************************/
/* Author: Max Sperling */
/************************/

#include "trans/trans_p2p/Outcome.hpp"
#include "view/IView.hpp"
#include "conf/IConf.hpp"
#include <QFile>
#include <QFileInfo>

using namespace std;

// ***** Public ************************************************************************************
Outcome::Outcome(IViewSPtr view, const shared_ptr<ConnectionDetails>& det,
                 const shared_ptr<IConLisVec>& lis, const string& file)
{
    m_view = view;
    m_conDet = det;
    m_conLis = lis;
    m_filePath = file;
    m_logIdent = "[Client]";
}

Outcome::~Outcome()
{
    for (IConnectionListener* lis : *m_conLis)
    {
        lis->onConnectionFinished(m_filePath, IConnectionListener::ConnectionType::OUTGOING);
    }
}
// *************************************************************************************************

// ***** Protected *********************************************************************************
void Outcome::run()
{
    m_socket = new QTcpSocket();

    connect(m_socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));

    if (!connectToServer()) return;
    if (!sendFile()) return;

    exec();
}
// *************************************************************************************************

// ***** Private ***********************************************************************************
bool Outcome::connectToServer()
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

    return true;
}

bool Outcome::sendFile()
{
    QFile file(QByteArray::fromStdString(m_filePath));

    if (!file.open(QFile::ReadOnly))
    {
        m_view->logIt(m_logIdent + " Can't open file");
        return false;
    }

    QFileInfo fileInfo(file);
    QString name = fileInfo.fileName();
    QByteArray content = file.readAll();

    m_view->logIt(m_logIdent + " Sending file: " + m_filePath
                                 + ", Content size: " + std::to_string(content.size()));

    QDataStream socketStream(m_socket);
    socketStream << name << content;

    file.close();

    m_socket->waitForBytesWritten(-1);
    m_socket->disconnectFromHost();

    return true;
}
// *************************************************************************************************

// ***** Private Slots *****************************************************************************
void Outcome::onDisconnected()
{
    m_view->logIt(m_logIdent + " Disconnected");

    m_socket->close();
    quit();
}
// *************************************************************************************************
