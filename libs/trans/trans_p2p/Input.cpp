/************************/
/* Author: Max Sperling */
/************************/

#include "trans/trans_p2p/Input.hpp"

#include "conf/IConf.hpp"
#include "trans/trans_p2p/TransP2P.hpp"
#include "trans/ITrans.hpp"

#include <QDir>
#include <QFile>

using namespace std;

namespace
{
    bool openFile(QFile& file, const QFlags<QIODevice::OpenMode::enum_type> mode, const view::ILoggerSPtr& logger, const std::string& logIdent)
    {
        bool isOpen = file.open(mode);

        if (!isOpen)
        {
            logger->logIt(logIdent + " Can't open file " + file.fileName().toStdString());
            return false;
        }

        return true;
    }
}

namespace trans::trans_p2p
{
    // ***** Public ***************************************************************************************************
    Input::Input(const view::ILoggerSPtr& log, const shared_ptr<conf::ConnectionDetails>& det,
                 ISerLisVec& lis, qintptr socketId)
    : m_serLis(lis)
    {
        m_logger = log;
        m_conDet = det;
        m_logIdent = "[Server][" + to_string(socketId) + "]";
        m_socket = nullptr;
        m_socketId = socketId;
        m_fileName = "";
    }

    Input::~Input()
    {
        for (IServerListener& lis : m_serLis)
        {
            lis.onConnectionFinished(m_socketId, m_fileName);
        }
    }
    // ****************************************************************************************************************

    // ***** Protected ************************************************************************************************
    void Input::run()
    {
        m_socket = new QTcpSocket();
        // m_socket->setSocketOption(QAbstractSocket::ReceiveBufferSizeSocketOption, QVariant::fromValue(max_packet_payload_size));

        if (!m_socket->setSocketDescriptor(m_socketId))
        {
            m_logger->logIt(m_logIdent + " Can't setup socket");
            return;
        }

        connect(m_socket, SIGNAL(readyRead()), this, SLOT(onReceivedData()));
        connect(m_socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));

        m_logger->logIt(m_logIdent + " Connected");

        exec();
    }
    // ****************************************************************************************************************

    // ***** Slots ****************************************************************************************************
    void Input::onReceivedData()
    {
        if (m_fileName.empty())
        {
            QDir().mkdir(QString::fromStdString(m_conDet->m_dir));

            const auto curTime = std::chrono::system_clock::now();
            m_fileName = std::format("{:%Y-%m-%d %H:%M:%S}", curTime) + ".zip";

            for (IServerListener& lis : m_serLis)
            {
                lis.onFirstDataReceived(m_socketId, m_fileName);
            }

            string filePath = m_conDet->m_dir + "/" + m_fileName;
            QFile file(QString::fromStdString(filePath));

            {
                constexpr QFlags mode = QIODevice::WriteOnly;
                if (!openFile(file, mode, m_logger, m_logIdent)) { return; }
            }

            file.resize(0);
            file.close();

            m_logger->logIt(m_logIdent + " Created file: " + m_fileName);
        }

        if (!m_fileName.empty() && m_socket->bytesAvailable())
        {
            string filePath = m_conDet->m_dir + "/" + m_fileName;
            QFile file(QString::fromStdString(filePath));

            {
                constexpr QFlags mode = (QIODevice::WriteOnly | QIODevice::Append);
                if (!openFile(file, mode, m_logger, m_logIdent)) { return; }
            }

            while (m_socket->bytesAvailable())
            {
                QByteArray content = m_socket->readAll();

                m_logger->logIt(m_logIdent + " Received data for file: " + m_fileName + ", Content size: " + std::to_string(content.size()));

                file.write(content);
            }

            file.close();
        }
    }

    void Input::onDisconnected()
    {
        m_logger->logIt(m_logIdent + " Disconnected");

        m_socket->close();
        quit();
    }
    // ****************************************************************************************************************
}
