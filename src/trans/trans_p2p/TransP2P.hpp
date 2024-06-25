#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "trans/ITrans.hpp"
#include "conf/IConfFwd.hpp"
#include <memory>
#include <vector>

#include "trans/trans_p2p/Server.hpp"
#include "trans/trans_p2p/Client.hpp"

namespace trans
{
    namespace trans_p2p
    {
        class TransP2P : public ITrans
        {
        public:
            // --- ITrans ----------------------------
            bool exec(const view::IViewSPtr& view, const conf::IConDetSPtr& conDet) override;
            bool attach(IConnectionListener* lis) override;
            bool detach(IConnectionListener* lis) override;
            // ---------------------------------------

        private:
            std::shared_ptr<IConLisVec> m_conLis;

            std::unique_ptr<Server> m_server;
            std::unique_ptr<Client> m_client;
        };
    }
}
