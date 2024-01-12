/************************/
/* Author: Max Sperling */
/************************/

#include "trans/trans_p2p/Income.hpp"
#include "trans/ITrans.hpp"
#include "conf/IConf.hpp"
#include <QDir>
#include <QFile>

using namespace std;

// ***** Public ************************************************************************************
Income::Income(IViewSPtr view, const shared_ptr<ConnectionDetails>& det,
               const shared_ptr<IConLisVec>& lis, qintptr socketId)
{
    m_view = view;
    m_conDet = det;
    m_conLis = lis;
    m_socketId = socketId;
    m_fileName = "";
    m_logIdent = "[Server][" + to_string(m_socketId) + "]";
}

Income::~Income()
{
    for (IConnectionListener* lis : *m_conLis)
    {
        lis->onConnectionFinished(m_fileName, IConnectionListener::ConnectionType::INCOMING);
    }
}
// *************************************************************************************************

// ***** Protected *********************************************************************************
void Income::run()
{
    m_socket = new QTcpSocket();

    if(!m_socket->setSocketDescriptor(m_socketId))
    {
        m_view->logIt(m_logIdent + " Can't setup socket");
        return;
    }

    connect(m_socket, SIGNAL(readyRead()), this, SLOT(onGotTCPStream()));
    connect(m_socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));

    m_view->logIt(m_logIdent + " Connected");

    exec();
}
// *************************************************************************************************

// ***** Slots *************************************************************************************
void Income::onGotTCPStream()
{
    QByteArray data = m_socket->readAll();
    QDataStream datastream(data);

    bool isInit = m_fileName.empty();
    if(isInit)
    {
        QDir().mkdir(QString::fromStdString(m_conDet->m_dir));

        QString name;
        datastream >> name;
        m_fileName = name.toStdString();
    }

    QByteArray content;
    datastream >> content;

    string filePath = m_conDet->m_dir + "/" + m_fileName;
    QFile file(QString::fromStdString(filePath));

    bool isOpen = isInit ? file.open(QIODevice::WriteOnly)
                         : file.open(QIODevice::WriteOnly | QIODevice::Append);
    if (!isOpen)
    {
        m_view->logIt(m_logIdent + " Can't open file");
        return;
    }
    m_view->logIt(m_logIdent + " Writing: " + m_fileName);

    file.write(content);
    file.close();
}

void Income::onDisconnected()
{
    m_view->logIt(m_logIdent + " Disconnected");

    m_socket->close();
    quit();
}
// *************************************************************************************************
