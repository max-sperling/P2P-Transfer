/************************/
/* Author: Max Sperling */
/************************/

#include "trans/trans_p2p/Client.hpp"
#include "trans/trans_p2p/Outcome.hpp"

using namespace std;

// ***** Public ************************************************************************************
Client::Client(IViewSPtr view, const shared_ptr<ConnectionDetails>& det, const shared_ptr<IConLisVec>& lis)
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

void Client::onSendTriggered(const string& file)
{
    Outcome* outcome = new Outcome(m_view, m_conDet, m_conLis, file);
    connect(outcome, SIGNAL(finished()), outcome, SLOT(deleteLater()));
    outcome->start();
}
// *************************************************************************************************
