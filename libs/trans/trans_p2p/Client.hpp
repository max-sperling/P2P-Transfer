#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "conf/IConfFwd.hpp"
#include "trans/ITrans.hpp"
#include "view/IView.hpp"

#include <QObject>

#include <memory>
#include <string>
#include <vector>

namespace trans::trans_p2p
{
    class Client : public QObject
    {
        Q_OBJECT

    public:
        /**
         * @param[in] log ... Logger
         * @param[in] det ... Connection details
         */
        Client(const view::ILoggerSPtr& log, const std::shared_ptr<conf::ConnectionDetails>& det);
        ~Client() override;

        /**
         * @param[in] items ... Items paths
         */
        void sendFiles(const std::vector<std::string>& items);

    private:
        view::ILoggerSPtr m_logger;
        std::shared_ptr<conf::ConnectionDetails> m_conDet;
    };
}
