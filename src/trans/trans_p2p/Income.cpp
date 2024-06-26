/************************/
/* Author: Max Sperling */
/************************/

#include "trans/trans_p2p/Income.hpp"
#include "trans/ITrans.hpp"
#include "conf/IConf.hpp"
#include <QDir>
#include <QFile>

using namespace std;

namespace {
    bool openFile(QFile& file, QIODevice::OpenModeFlag mode, const view::IViewSPtr view, std::string logIdent)
    {
        bool isOpen = file.open(QIODevice::WriteOnly | QIODevice::Append);

        if (!isOpen)
        {
            view->logIt(logIdent + " Can't open file " + file.fileName().toStdString());
            return false;
        }

        return true;
    }
}

namespace trans
{
    namespace trans_p2p
    {
        // ***** Public ************************************************************************************
        Income::Income(view::IViewSPtr view, const shared_ptr<conf::ConnectionDetails>& det,
                       const shared_ptr<IConLisVec>& lis, qintptr socketId)
        {
            m_view = view;
            m_conDet = det;
            m_conLis = lis;
            m_socketId = socketId;
            m_fileName = "";
            m_logIdent = "[Server][" + to_string(m_socketId) + "]";
            m_socket = nullptr;
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

            connect(m_socket, SIGNAL(readyRead()), this, SLOT(onReceivedData()));
            connect(m_socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));

            m_view->logIt(m_logIdent + " Connected");

            exec();
        }
        // *************************************************************************************************

        // ***** Slots *************************************************************************************
        void Income::onReceivedData()
        {
            if (m_fileName.empty() && m_socket->canReadLine())
            {
                QDir().mkdir(QString::fromStdString(m_conDet->m_dir));

                QString name = QString::fromUtf8(m_socket->readLine()).trimmed();
                m_fileName = name.toStdString();

                string filePath = m_conDet->m_dir + "/" + m_fileName;
                QFile file(QString::fromStdString(filePath));

                if (!openFile(file, QIODevice::WriteOnly, m_view, m_logIdent)) { return; }
                file.resize(0);
                file.close();

                m_view->logIt(m_logIdent + " Created file: " + m_fileName);
            }

            if (!m_fileName.empty() && m_socket->bytesAvailable())
            {
                string filePath = m_conDet->m_dir + "/" + m_fileName;
                QFile file(QString::fromStdString(filePath));

                if (!openFile(file, QIODevice::Append, m_view, m_logIdent)) { return; }

                while (m_socket->bytesAvailable())
                {
                    QByteArray content = m_socket->readAll();

                    m_view->logIt(m_logIdent + " Received data for file: " + m_fileName
                                                 + ", Content size: " + std::to_string(content.size()));

                    file.write(content);
                }

                file.close();
            }
        }

        void Income::onDisconnected()
        {
            m_view->logIt(m_logIdent + " Disconnected");

            m_socket->close();
            quit();
        }
        // *************************************************************************************************
    }
}
