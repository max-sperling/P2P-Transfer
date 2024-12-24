#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "conf/IConfFwd.hpp"
#include "trans/ITransFwd.hpp"
#include "view/IView.hpp"

namespace trans
{
    class ITrans : public view::IViewListener
    {
    public:
        virtual ~ITrans() = default;

        /**
         * @param[in] logger ... Logger
         * @param[in] conDet ... Connection details
         */
        virtual bool exec(const view::ILoggerSPtr& logger, const conf::IConDetSPtr& conDet) = 0;

        /**
         * @param[in] lis ... Server listener
         */
        virtual bool attach(const ISerLisWPtr& lis) = 0;

        /**
         * @param[in] lis ... Server listener
         */
        virtual bool detach(const ISerLisWPtr& lis) = 0;
    };

    class IServerListener
    {
    public:
        virtual ~IServerListener() = default;

        /**
         * @param[in] socketId ... Socket id
         * @param[in] fileName ... Name of the zip file
         */
        virtual void onFirstDataReceived(long long socketId, const std::string& fileName) = 0;

        /**
         * @param[in] socketId ... Socket id
         * @param[in] fileName ... Name of the zip file
         */
        virtual void onConnectionFinished(long long socketId, const std::string& fileName) = 0;
    };
}
