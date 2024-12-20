/************************/
/* Author: Max Sperling */
/************************/

#include "trans/trans_p2p/Client.hpp"

#include "trans/trans_p2p/Output.hpp"

using namespace std;

namespace trans::trans_p2p
{
    // ***** Public ***************************************************************************************************
    Client::Client(const view::ILoggerSPtr& log, const shared_ptr<conf::ConnectionDetails>& det, const shared_ptr<IConLisVec>& lis)
    : m_logger(log), m_conDet(det), m_conLis(lis) {}

    Client::~Client()
    {
    }

    void Client::sendFiles(const vector<string>& items)
    {
        auto* output = new Output(m_logger, m_conDet, m_conLis, items);
        connect(output, SIGNAL(finished()), output, SLOT(deleteLater()));
        output->start();
    }
    // ****************************************************************************************************************
}
