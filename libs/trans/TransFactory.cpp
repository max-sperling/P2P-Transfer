/************************/
/* Author: Max Sperling */
/************************/

#include "trans/TransFactory.hpp"
#include "trans/trans_p2p/TransP2P.hpp"

using namespace std;

namespace trans
{
    ITransSPtr TransFactory::create(const TransType type)
    {
        ITransSPtr transPtr;

        switch (type)
        {
            case TransType::P2P:
                transPtr = make_shared<trans_p2p::TransP2P>();
            break;
        }

        return transPtr;
    }
}
