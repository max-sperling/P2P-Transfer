#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "trans/ITransFwd.hpp"

class TransFactory
{
public:
    static ITransSPtr create(const TransType type);
};
