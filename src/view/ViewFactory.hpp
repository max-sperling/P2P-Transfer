#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "view/IViewFwd.hpp"

namespace view
{
    class ViewFactory
    {
    public:
        static IViewSPtr create(const ViewType type);
    };
}
