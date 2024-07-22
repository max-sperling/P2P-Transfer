#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "conf/IConfFwd.hpp"

namespace conf
{
    class ConfFactory
    {
    public:
        static IConfSPtr create(const ConfType type);
    };
}