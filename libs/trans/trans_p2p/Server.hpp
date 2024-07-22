#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "trans/ITrans.hpp"
#include "view/IViewFwd.hpp"
#include "conf/IConfFwd.hpp"
#include <QTcpServer>
#include <memory>
#include <string>

namespace trans::trans_p2p
{
    class Server : public QTcpServer
    {
        Q_OBJECT

    public:
        /**
         * @param[in] view ... View
         * @param[in] det  ... Connection details
         * @param[in] lis  ... Connection listener
         */
        Server(const view::IViewSPtr& view, const std::shared_ptr<conf::ConnectionDetails>& det, const std::shared_ptr<IConLisVec>& lis);
        ~Server() override = default;

        bool init();

    protected:
        void incomingConnection(qintptr socketId) override;

    private:
        view::IViewSPtr m_view;

        std::shared_ptr<conf::ConnectionDetails> m_conDet;
        std::shared_ptr<IConLisVec> m_conLis;
    };
}
