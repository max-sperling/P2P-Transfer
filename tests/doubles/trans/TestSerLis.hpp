#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "trans/ITrans.hpp"

#include <QCoreApplication>

namespace trans
{
    class TestSerLis : public trans::IServerListener
    {
    public:
        TestSerLis(QCoreApplication& app, std::string& fileName);

        // --- IServerListener -------------------
        void onFirstDataReceived(long long socketId, const std::string& fileName) override;
        void onConnectionFinished(long long socketId, const std::string& fileName) override;
        // ---------------------------------------

    private:
        QCoreApplication& m_app;
        std::string& m_fileName;
    };
}