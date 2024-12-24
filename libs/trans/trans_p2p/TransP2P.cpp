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

    bool TransP2P::attach(const ISerLisWPtr& lis)
    {
        auto lockedLis = lis.lock();
        if (!lockedLis) { return false; }

        auto iter = find_if(m_serLis.begin(), m_serLis.end(), [&lockedLis](const auto& item)
        {
            if (auto lockedItem = item.lock())
            {
                if (lockedItem == lockedLis) { return true; }
            }
            return false;
        });
        if (iter != m_serLis.end()) { return false; }

        m_serLis.push_back(lis);
        return true;
    }

    bool TransP2P::detach(const ISerLisWPtr& lis)
    {
        auto lockedLis = lis.lock();
        if (!lockedLis) { return false; }

        auto iter = find_if(m_serLis.begin(), m_serLis.end(), [&lockedLis](const auto& item)
        {
            if (auto lockedItem = item.lock())
            {
                if (lockedItem == lockedLis) { return true; }
            }
            return false;
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
