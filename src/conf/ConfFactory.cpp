/************************/
/* Author: Max Sperling */
/************************/

#include "ConfFactory.hpp"
#include "conf_json/ConfJson.hpp"

using namespace std;

IConfPtr ConfFactory::create(ConfType type)
{
    IConfPtr confPtr;
    switch(type)
    {
    case ConfType::Json:
        confPtr = make_shared<ConfJson>();
        break;
    }
    return confPtr;
}
