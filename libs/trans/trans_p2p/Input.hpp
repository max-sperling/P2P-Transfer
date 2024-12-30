#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "conf/IConfFwd.hpp"
#include "trans/ITransFwd.hpp"
#include "view/IView.hpp"

#include <QFile>
#include <QThread>
#include <QTcpSocket>

#include <memory>
#include <string>

namespace trans::trans_p2p
{
    class Input : public QObject
    {
        Q_OBJECT

    public:
        Input(const view::ILoggerSPtr& log, const std::shared_ptr<conf::ConnectionDetails>& det,
              ISerLisVec& lis, qintptr socketId);
        ~Input() override;

    public slots:
        void start();

    private:
        bool openFile(QFile& file, const QFlags<QIODevice::OpenMode::enum_type> mode);
        void createFile();
        void writeFile();
        void cleanupSocket();

        view::ILoggerSPtr m_logger;
        std::string m_logIdent;

        std::shared_ptr<conf::ConnectionDetails> m_conDet;
        ISerLisVec& m_serLis;

        QTcpSocket* m_socket;
        qintptr m_socketId;

        std::string m_fileName;

    private slots:
        void onDataReceived();
        void onDisconnected();

    signals:
        void finished();
    };
}
