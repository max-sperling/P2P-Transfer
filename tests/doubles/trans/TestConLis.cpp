/************************/
/* Author: Max Sperling */
/************************/

#include "trans/TestConLis.hpp"

namespace trans
{
    TestConLis::TestConLis(QCoreApplication& app) : m_app(app) {}

    void TestConLis::onConnectionStarted(long long socketId, IConnectionListener::ConnectionType type) {}

    void TestConLis::onConnectionFinished(long long socketId, IConnectionListener::ConnectionType type)
    {
        if (type == IConnectionListener::ConnectionType::INCOMING)
        {
            m_app.quit();
        }
    }
}
