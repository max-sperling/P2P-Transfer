/************************/
/* Author: Max Sperling */
/************************/

#include "trans/TransFactory.hpp"
#include "trans/trans_p2p/TransP2P.hpp"

using namespace std;

ITransSPtr TransFactory::create(const TransType type)
{
    ITransSPtr transPtr;

    switch (type)
    {
    case TransType::P2P:
        transPtr = make_shared<TransP2P>();
        break;
    }

    return transPtr;
}
