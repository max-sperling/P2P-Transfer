#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "trans/ITransFwd.hpp"
#include "conf/IConfFwd.hpp"
#include "view/IViewFwd.hpp"

class ITrans
{
public:
    virtual ~ITrans(){}

    /**
     * @param[in] viewPtr ... View
     * @param[in] confPtr ... Conf
     */
    virtual bool init(const IViewSPtr& view, const IConfSPtr& conf) = 0;

    /**
     * @param[in] argc ... Argument count
     * @param[in] argv ... Argument vector
     */
    virtual bool exec(int argc, char *argv[]) = 0;

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
    virtual ~IConnectionListener() {}

    enum ConnectionType { OUTGOING, INCOMING };

    /**
     * @param[in] file ... File name
     * @param[in] type ... Connection type
     */
    virtual void onConnectionStarted(const std::string& file,
        const ConnectionType type) = 0;

    /**
     * @param[in] file ... File name
     * @param[in] type ... Connection type
     */
    virtual void onConnectionFinished(const std::string& file,
        const ConnectionType type) = 0;
};
