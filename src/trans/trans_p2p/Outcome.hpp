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

class Outcome : public QThread
{
    Q_OBJECT

public:
    Outcome(IViewSPtr view, const std::shared_ptr<ConnectionDetails>& det,
            const std::shared_ptr<IConLisVec>& lis, const std::string& file);
    ~Outcome() override;

protected:
    void run() override;

private:
    bool connectToServer();
    bool sendFile();

    IViewSPtr m_view;

    std::shared_ptr<ConnectionDetails> m_conDet;
    std::shared_ptr<IConLisVec> m_conLis;

    std::string m_filePath;
    std::string m_logIdent;

    QTcpSocket* m_socket;

private slots:
    void onDisconnected();
};