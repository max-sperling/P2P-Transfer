#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include <memory>

namespace view
{
    enum ViewType { Qute };

    class IView;
    class IViewListener;

    typedef std::shared_ptr<IView> IViewSPtr;
}
