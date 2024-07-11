#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "trans/ITrans.hpp"
#include "view/IViewFwd.hpp"
#include "conf/IConfFwd.hpp"
#include <QThread>
#include <QTcpSocket>
#include <QFile>
#include <memory>
#include <string>

namespace trans
{
    namespace trans_p2p
    {
        class Output : public QThread
        {
            Q_OBJECT

        public:
            Output(view::IViewSPtr view, const std::shared_ptr<conf::ConnectionDetails>& det,
                   const std::shared_ptr<IConLisVec>& lis, const std::vector<std::string>& items);
            ~Output() override;

        protected:
            void run() override;

        private:
            bool sendItems();
            bool connectToServer();
            bool disconnectFromServer();

            view::IViewSPtr m_view;

            std::shared_ptr<conf::ConnectionDetails> m_conDet;
            std::shared_ptr<IConLisVec> m_conLis;

            std::vector<std::string> m_items;
            std::string m_logIdent;

            QTcpSocket* m_socket;
            qintptr m_socketId;

        private slots:
            void onDisconnected();
        };
    }
}
