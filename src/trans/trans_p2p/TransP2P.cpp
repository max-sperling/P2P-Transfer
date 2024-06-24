/************************/
/* Author: Max Sperling */
/************************/

#include "trans/trans_p2p/TransP2P.hpp"
#include "conf/IConf.hpp"

using namespace std;

namespace trans
{
    namespace trans_p2p
    {
        bool TransP2P::init(const view::IViewSPtr& view, const conf::IConfSPtr& conf)
        {
            m_view = view;
            m_conf = conf;

            return true;
        }

        bool TransP2P::exec()
        {
            m_view->start();

            m_conDet = make_shared<conf::ConnectionDetails>();
            if (!m_conf->read(*m_conDet))
            {
                m_view->logIt("Error while reading Config");
                return false;
            }

            m_conLis = make_shared<IConLisVec>();

            m_server = make_unique<Server>(m_view, m_conDet, m_conLis);
            if (!m_server->init())
            {
                m_view->logIt("Error while init Server");
                return false;
            }

            m_client = make_unique<Client>(m_view, m_conDet, m_conLis);

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
    }
}
