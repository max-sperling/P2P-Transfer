/************************/
/* Author: Max Sperling */
/************************/

#include "trans/TestSerLis.hpp"

namespace trans
{
    TestSerLis::TestSerLis(QCoreApplication& app, std::string& fileName)
    : m_app(app), m_fileName(fileName) {}

    void TestSerLis::onFirstDataReceived(long long socketId, const std::string& fileName)
    {
        m_fileName = fileName;
    }

    void TestSerLis::onConnectionFinished(long long socketId, const std::string& fileName)
    {
        m_app.quit();
    }
}
