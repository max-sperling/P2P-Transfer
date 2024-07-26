#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "view/IView.hpp"
#include "trans/ITransFwd.hpp"
#include "conf/IConfFwd.hpp"

#include <archive.h>
#include <archive_entry.h>
#include <QThread>
#include <QTcpSocket>
#include <filesystem>
#include <fstream>
#include <memory>
#include <string>
#include <unordered_map>

namespace trans::trans_p2p
{
    struct InputClientData
    {
        std::vector<char> m_dataBuffer;
    };

    class Input : public QThread
    {
        Q_OBJECT

    public:
        Input(const view::IViewSPtr& view, const std::shared_ptr<conf::ConnectionDetails>& det,
              const std::shared_ptr<IConLisVec>& lis, qintptr socketId);
        ~Input() override;

    protected:
        void run() override;

    private:
        void unzipFileFromMemory(const QByteArray& receivedData, const std::filesystem::path& outputFolder);

        view::IViewSPtr m_view;
        std::string m_logIdent;

        std::shared_ptr<conf::ConnectionDetails> m_conDet;
        std::shared_ptr<IConLisVec> m_conLis;

        QTcpSocket* m_socket;
        qintptr m_socketId;

        QByteArray m_receivedData;

    private slots:
        void onReceivedData();
        void onDisconnected();
    };
}
