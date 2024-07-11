/************************/
/* Author: Max Sperling */
/************************/

#include "trans/trans_p2p/Client.hpp"
#include "trans/trans_p2p/Output.hpp"

using namespace std;

namespace trans::trans_p2p
{
    // ***** Public ************************************************************************************
    Client::Client(const view::IViewSPtr& view, const shared_ptr<conf::ConnectionDetails>& det, const shared_ptr<IConLisVec>& lis)
    {
        m_view = view;
        m_conDet = det;
        m_conLis = lis;

        m_view->attach(this);
    }

    Client::~Client()
    {
        m_view->detach(this);
    }

    void Client::onSendTriggered(const vector<string>& items)
    {
        auto* output = new Output(m_view, m_conDet, m_conLis, items);
        connect(output, SIGNAL(finished()), output, SLOT(deleteLater()));
        output->start();
    }
    // *************************************************************************************************
}
