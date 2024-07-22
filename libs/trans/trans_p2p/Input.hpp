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

namespace trans::trans_p2p
{
    class Input : public QThread
    {
        Q_OBJECT

    public:
        Input(const view::IViewSPtr& view, const std::shared_ptr<conf::ConnectionDetails>& det,
              const std::shared_ptr<IConLisVec>& lis, qintptr socketId);
        ~Input() override;

    protected:
        void run() override;

    private:
        view::IViewSPtr m_view;
        std::string m_logIdent;

        std::shared_ptr<conf::ConnectionDetails> m_conDet;
        std::shared_ptr<IConLisVec> m_conLis;

        QTcpSocket* m_socket;
        qintptr m_socketId;

        std::string m_fileName;

    private slots:
        void onReceivedData();
        void onDisconnected();
    };
}
