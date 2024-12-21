#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include <memory>
#include <vector>

namespace view
{
    enum ViewType { Qute };

    class IView;
    class ILogger;
    class IViewListener;

    typedef std::shared_ptr<IView> IViewSPtr;
    typedef std::shared_ptr<ILogger> ILoggerSPtr;
    typedef std::weak_ptr<IViewListener> IViewLisWPtr;
    typedef std::vector<IViewLisWPtr> IViewLisVec;
}
