#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "conf/IConfFwd.hpp"
#include "trans/ITransFwd.hpp"
#include "view/IViewFwd.hpp"

namespace trans
{
    class ITrans
    {
    public:
        virtual ~ITrans() = default;

        /**
         * @param[in] view   ... View
         * @param[in] conDet ... Connection details
         */
        virtual bool exec(const view::IViewSPtr& view, const conf::IConDetSPtr& conDet) = 0;

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
         * @param[in] socketId ... Socket id
         * @param[in] type ... Connection type
         */
        virtual void onConnectionStarted(long long socketId, ConnectionType type) = 0;

        /**
         * @param[in] socketId ... Socket id
         * @param[in] type ... Connection type
         */
        virtual void onConnectionFinished(long long socketId, ConnectionType type) = 0;
    };
}
