#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "conf/IConfFwd.hpp"
#include "trans/ITrans.hpp"
#include "view/IViewFwd.hpp"

#include <QThread>
#include <QTcpSocket>

#include <memory>
#include <string>

namespace trans::trans_p2p
{
    class Output : public QThread
    {
        Q_OBJECT

    public:
        Output(const view::ILoggerSPtr& log, const std::shared_ptr<conf::ConnectionDetails>& det, const std::vector<std::string>& items);
        ~Output() override = default;

    protected:
        void run() override;

    private:
        bool sendItems();
        bool connectToServer();
        bool disconnectFromServer();

        view::ILoggerSPtr m_logger;

        std::shared_ptr<conf::ConnectionDetails> m_conDet;

        std::vector<std::string> m_items;
        std::string m_logIdent;

        QTcpSocket* m_socket;
        qintptr m_socketId;

    private slots:
        void onDisconnected();
    };
}
