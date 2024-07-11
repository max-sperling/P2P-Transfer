#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "trans/ITrans.hpp"
#include "view/IView.hpp"
#include "conf/IConfFwd.hpp"
#include <QObject>
#include <memory>
#include <string>

namespace trans
{
    namespace trans_p2p
    {
        class Client : public QObject, public view::IViewListener
        {
            Q_OBJECT

        public:
            /**
             * @param[in] view ... View
             * @param[in] det  ... Connection details
             * @param[in] lis  ... Connection listener
             */
            Client(view::IViewSPtr view, const std::shared_ptr<conf::ConnectionDetails>& det, const std::shared_ptr<IConLisVec>& lis);
            ~Client() override;

            // --- IViewListener ---------------------
            void onSendTriggered(const std::vector<std::string>& items) override;
            // ---------------------------------------

        private:
            view::IViewSPtr m_view;

            std::shared_ptr<conf::ConnectionDetails> m_conDet;
            std::shared_ptr<IConLisVec> m_conLis;
        };
    }
}
