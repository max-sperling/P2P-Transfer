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
        class Outcome : public QThread
        {
            Q_OBJECT

        public:
            Outcome(view::IViewSPtr view, const std::shared_ptr<conf::ConnectionDetails>& det,
                    const std::shared_ptr<IConLisVec>& lis, const std::string& file);
            ~Outcome() override;

        protected:
            void run() override;

        private:
            bool connectToServer();
            bool sendFile();

            view::IViewSPtr m_view;

            std::shared_ptr<conf::ConnectionDetails> m_conDet;
            std::shared_ptr<IConLisVec> m_conLis;

            std::string m_filePath;
            std::string m_logIdent;

            QTcpSocket* m_socket;

            private slots:
                void onDisconnected();
        };
    }
}
