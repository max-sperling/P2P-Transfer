#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "view/IViewFwd.hpp"

class ViewFactory
{
public:
    static IViewSPtr create(const ViewType type);
};
