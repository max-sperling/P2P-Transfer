#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "conf/IConfFwd.hpp"

class ConfFactory
{
public:
    static IConfSPtr create(const ConfType type);
};