#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "view/IViewFwd.hpp"
#include <string>

class IView
{
public:
    virtual ~IView() = default;

    virtual bool start() = 0;

    /**
     * @param[in] msg ... Log message
     */
    virtual void logIt(const std::string& msg) = 0;

    /**
     * @param[in] lis ... View listener
     */
    virtual bool attach(IViewListener* lis) = 0;

    /**
     * @param[in] lis ... View listener
     */
    virtual bool detach(IViewListener* lis) = 0;
};

class IViewListener
{
public:
    virtual ~IViewListener() = default;

    /**
     * @param[in] file ... File path
     */
    virtual void onSendTriggered(const std::string& file) = 0;
};
