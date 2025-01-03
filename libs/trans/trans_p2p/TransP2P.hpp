#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "conf/IConfFwd.hpp"
#include "trans/ITrans.hpp"
#include "trans/trans_p2p/Client.hpp"
#include "trans/trans_p2p/Server.hpp"

#include <memory>

namespace trans::trans_p2p
{
    class TransP2P : public ITrans
    {
    public:
        // --- ITrans ----------------------------
        bool exec(const view::ILoggerSPtr& logger, const conf::IConDetSPtr& conDet) override;
        bool attach(const ISerLisWPtr& lis) override;
        bool detach(const ISerLisWPtr& lis) override;
        // ---------------------------------------

        // --- IViewListener ---------------------
        void onSendTriggered(const std::vector<std::string>& items) override;
        // ---------------------------------------

    private:
        ISerLisVec m_serLis;

        std::unique_ptr<Server> m_server;
        std::unique_ptr<Client> m_client;
    };
}
