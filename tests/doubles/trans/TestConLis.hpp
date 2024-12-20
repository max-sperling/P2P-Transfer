#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "trans/ITrans.hpp"

#include <QCoreApplication>

namespace trans
{
    class TestConLis : public trans::IConnectionListener
    {
    public:
        TestConLis(QCoreApplication& app);

        // --- IConnectionListener ---------------
        void onConnectionStarted(long long socketId, IConnectionListener::ConnectionType type) override;
        void onConnectionFinished(long long socketId, IConnectionListener::ConnectionType type) override;
        // ---------------------------------------

    private:
        QCoreApplication& m_app;
    };
}