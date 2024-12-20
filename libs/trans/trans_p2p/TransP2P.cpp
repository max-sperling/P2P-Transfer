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
        m_conLis = make_shared<IConLisVec>();

        m_client = make_unique<Client>(logger, conDet, m_conLis);

        m_server = make_unique<Server>(logger, conDet, m_conLis);
        if (!m_server->init())
        {
            logger->logIt("Can't initialize server");
            return false;
        }

        return true;
    }

    bool TransP2P::attach(IConnectionListener* lis)
    {
        if (m_conLis)
        {
            auto iter = find(m_conLis->begin(), m_conLis->end(), lis);
            if (iter != m_conLis->end()) return false;

            m_conLis->push_back(lis);
        }

        return true;
    }

    bool TransP2P::detach(IConnectionListener* lis)
    {
        if (m_conLis)
        {
            auto iter = find(m_conLis->begin(), m_conLis->end(), lis);
            if (iter == m_conLis->end()) return false;

            m_conLis->erase(iter);
        }

        return true;
    }

    void TransP2P::onSendTriggered(const vector<string>& items)
    {
        m_client->sendFiles(items);
    }
    // ****************************************************************************************************************
}
