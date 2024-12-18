/************************/
/* Author: Max Sperling */
/************************/

#include "conf/ConfFactory.hpp"

#include "conf/conf_json/ConfJson.hpp"

using namespace std;

namespace conf
{
    IConfSPtr ConfFactory::create(const ConfType type)
    {
        IConfSPtr confPtr;

        switch (type)
        {
            case ConfType::Json:
                confPtr = make_shared<conf_json::ConfJson>();
            break;
        }

        return confPtr;
    }
}
