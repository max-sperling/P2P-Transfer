#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "trans/ITransFwd.hpp"
#include "conf/IConfFwd.hpp"
#include "view/IViewFwd.hpp"

namespace trans
{
    class ITrans
    {
    public:
        virtual ~ITrans() = default;

        /**
         * @param[in] viewPtr ... View
         */
        virtual bool init(const view::IViewSPtr& view) = 0;

        /**
         * @param[in] conDetails ... Connection details
         */
        virtual bool exec(const std::shared_ptr<conf::ConnectionDetails>& conDetails) = 0;

        /**
         * @param[in] lis ... Connection listener
         */
        virtual bool attach(IConnectionListener *lis) = 0;

        /**
         * @param[in] lis ... Connection listener
         */
        virtual bool detach(IConnectionListener *lis) = 0;
    };

    class IConnectionListener
    {
    public:
        virtual ~IConnectionListener() = default;

        enum ConnectionType { OUTGOING, INCOMING };

        /**
         * @param[in] file ... File name
         * @param[in] type ... Connection type
         */
        virtual void onConnectionStarted(const std::string& file, const ConnectionType type) = 0;

        /**
         * @param[in] file ... File name
         * @param[in] type ... Connection type
         */
        virtual void onConnectionFinished(const std::string& file, const ConnectionType type) = 0;
    };
}
