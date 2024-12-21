#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "view/IViewFwd.hpp"

#include <string>
#include <vector>

namespace view
{
    class ILogger
    {
    public:
        virtual ~ILogger() = default;

        /**
         * @param[in] msg ... Log message
         */
        virtual void logIt(const std::string& msg) = 0;
    };

    class IView : public ILogger
    {
    public:
        virtual ~IView() = default;

        virtual bool exec() = 0;

        /**
         * @param[in] lis ... View listener
         */
        virtual bool attach(const IViewLisWPtr& lis) = 0;

        /**
         * @param[in] lis ... View listener
         */
        virtual bool detach(const IViewLisWPtr& lis) = 0;
    };

    class IViewListener
    {
    public:
        virtual ~IViewListener() = default;

        /**
         * @param[in] items ... Item paths
         */
        virtual void onSendTriggered(const std::vector<std::string>& items) = 0;
    };
}
