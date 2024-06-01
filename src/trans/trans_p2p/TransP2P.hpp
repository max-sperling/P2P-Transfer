#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "trans/ITrans.hpp"
#include "conf/IConfFwd.hpp"
#include <memory>
#include <vector>

class Server;
class Client;

class TransP2P : public ITrans
{
public:
    TransP2P();
    ~TransP2P();

    // --- ITrans ----------------------------
    virtual bool init(const IViewSPtr& view, const IConfSPtr& conf) override;
    virtual bool exec() override;
    virtual bool attach(IConnectionListener* lis) override;
    virtual bool detach(IConnectionListener* lis) override;
    // ---------------------------------------

private:
    IViewSPtr m_view;
    IConfSPtr m_conf;

    std::shared_ptr<ConnectionDetails> m_conDet;
    std::shared_ptr<IConLisVec> m_conLis;

    std::unique_ptr<Server> m_server;
    std::unique_ptr<Client> m_client;
};
