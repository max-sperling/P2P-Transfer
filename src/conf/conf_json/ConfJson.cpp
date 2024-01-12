/************************/
/* Author: Max Sperling */
/************************/

#include "conf/conf_json/ConfJson.hpp"
#include "conf/conf_json/JsonParser.hpp"

using namespace std;

ConfJson::ConfJson() {}

ConfJson::~ConfJson() {}

bool ConfJson::read(ConnectionDetails& det)
{
    JsonParser parser;

    try
    {
        parser.parseFile("config.json");

        parser.getValStr("Addr", det.m_addr);
        parser.getValInt("Port", det.m_port);
        parser.getValStr("Dir",  det.m_dir);
    }
    catch (...)
    {
        return false;
    }

    return true;
}
