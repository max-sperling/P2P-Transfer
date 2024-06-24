/************************/
/* Author: Max Sperling */
/************************/

#include "conf/conf_json/ConfJson.hpp"
#include "conf/conf_json/JsonParser.hpp"

namespace conf
{
    namespace conf_json
    {
        bool ConfJson::read(ConnectionDetails& det)
        {
            try
            {
                JsonParser parser;
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
    }
}
