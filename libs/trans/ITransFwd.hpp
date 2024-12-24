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
    class IServerListener;

    typedef std::shared_ptr<ITrans> ITransSPtr;
    typedef std::weak_ptr<IServerListener> ISerLisWPtr;
    typedef std::vector<ISerLisWPtr> ISerLisVec;
}
