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

class Income : public QThread
{
    Q_OBJECT

public:
    Income(IViewSPtr view, const std::shared_ptr<ConnectionDetails>& det,
           const std::shared_ptr<IConLisVec>& lis, qintptr socketId);
    ~Income();

protected:
    void run() override;

private:
    IViewSPtr m_view;

    std::shared_ptr<ConnectionDetails> m_conDet;
    std::shared_ptr<IConLisVec> m_conLis;

    qintptr m_socketId;
    std::string m_fileName;
    std::string m_logIdent;

    QTcpSocket* m_socket;

private slots:
    void onGotTCPStream();
    void onDisconnected();
};
