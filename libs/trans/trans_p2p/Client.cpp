/************************/
/* Author: Max Sperling */
/************************/

#include "trans/trans_p2p/Client.hpp"

#include "trans/trans_p2p/Output.hpp"

using namespace std;

namespace trans::trans_p2p
{
    // ***** Public ***************************************************************************************************
    Client::Client(const view::ILoggerSPtr& log, const shared_ptr<conf::ConnectionDetails>& det)
    : m_logger(log), m_conDet(det) {}

    Client::~Client()
    {
    }

    void Client::sendFiles(const vector<string>& items)
    {
        QThread* thread = new QThread;
        Output* output = new Output(m_logger, m_conDet, items);

        output->moveToThread(thread);

        connect(thread, SIGNAL(started()), output, SLOT(start()));
        connect(output, SIGNAL(finished()), thread, SLOT(quit()));

        connect(output, SIGNAL(finished()), output, SLOT(deleteLater()));
        connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

        thread->start();
    }
    // ****************************************************************************************************************
}
