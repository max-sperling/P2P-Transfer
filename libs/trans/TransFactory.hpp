#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "trans/ITransFwd.hpp"

namespace trans
{
    class TransFactory
    {
    public:
        static ITransSPtr create(const TransType type);
    };
}
