#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "conf/IConfFwd.hpp"
#include "trans/ITrans.hpp"
#include "view/IViewFwd.hpp"

#include <QTcpServer>

#include <memory>
#include <string>

namespace trans::trans_p2p
{
    class Server : public QTcpServer
    {
        Q_OBJECT

    public:
        /**
         * @param[in] log ... Logger
         * @param[in] det ... Connection details
         * @param[in] lis ... Connection listener
         */
        Server(const view::ILoggerSPtr& log, const std::shared_ptr<conf::ConnectionDetails>& det, const std::shared_ptr<IConLisVec>& lis);
        ~Server() override = default;

        bool init();

    protected:
        void incomingConnection(qintptr socketId) override;

    private:
        view::ILoggerSPtr m_log;

        std::shared_ptr<conf::ConnectionDetails> m_conDet;
        std::shared_ptr<IConLisVec> m_conLis;
    };
}
