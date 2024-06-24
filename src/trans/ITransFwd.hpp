#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include <memory>
#include <vector>

namespace trans
{
    enum TransType { P2P };

    class ITrans;
    class IConnectionListener;

    typedef std::shared_ptr<ITrans> ITransSPtr;
    typedef std::vector<IConnectionListener*> IConLisVec;
}
