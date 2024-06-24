#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "view/IView.hpp"
#include "trans/ITransFwd.hpp"
#include "conf/IConfFwd.hpp"
#include <QThread>
#include <QTcpSocket>
#include <memory>
#include <string>

namespace trans
{
    namespace trans_p2p
    {
        class Income : public QThread
        {
            Q_OBJECT

        public:
            Income(view::IViewSPtr view, const std::shared_ptr<conf::ConnectionDetails>& det,
                   const std::shared_ptr<IConLisVec>& lis, qintptr socketId);
            ~Income() override;

        protected:
            void run() override;

        private:
            view::IViewSPtr m_view;

            std::shared_ptr<conf::ConnectionDetails> m_conDet;
            std::shared_ptr<IConLisVec> m_conLis;

            qintptr m_socketId;
            std::string m_fileName;
            std::string m_logIdent;

            QTcpSocket* m_socket;

            private slots:
                void onReceivedData();
            void onDisconnected();
        };
    }
}
