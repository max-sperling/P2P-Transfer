/************************/
/* Author: Max Sperling */
/************************/

#include "trans/trans_p2p/TransP2P.hpp"

#include "conf/IConf.hpp"

using namespace std;

namespace trans::trans_p2p
{
    // ***** Public ***************************************************************************************************
    bool TransP2P::exec(const view::ILoggerSPtr& logger, const conf::IConDetSPtr& conDet)
    {
        m_client = make_unique<Client>(logger, conDet);

        m_server = make_unique<Server>(logger, conDet, m_serLis);
        if (!m_server->init())
        {
            logger->logIt("Can't initialize server");
            return false;
        }

        return true;
    }

    bool TransP2P::attach(IServerListener& lis)
    {
        auto iter = find_if(m_serLis.begin(), m_serLis.end(), [&lis](const auto& item)
        {
            return &item.get() == &lis;
        });
        if (iter != m_serLis.end()) { return false; }
        m_serLis.push_back(std::ref(lis));

        return true;
    }

    bool TransP2P::detach(IServerListener& lis)
    {
        auto iter = find_if(m_serLis.begin(), m_serLis.end(), [&lis](const auto& item)
        {
            return &item.get() == &lis;
        });
        if (iter == m_serLis.end()) { return false; }
        m_serLis.erase(iter);

        return true;
    }

    void TransP2P::onSendTriggered(const vector<string>& items)
    {
        m_client->sendFiles(items);
    }
    // ****************************************************************************************************************
}
