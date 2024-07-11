/************************/
/* Author: Max Sperling */
/************************/

#include "conf/conf_json/ConfJson.hpp"
#include "conf/conf_json/JsonParser.hpp"

#include <filesystem>

namespace conf::conf_json
{
    bool ConfJson::read(const std::filesystem::path& configPath, ConnectionDetails& conDetails)
    {
        try
        {
            JsonParser parser;
            parser.parseFile(configPath);

            parser.getValStr("Addr", conDetails.m_addr);
            parser.getValInt("Port", conDetails.m_port);
            parser.getValStr("Dir",  conDetails.m_dir);
        }
        catch (...)
        {
            return false;
        }

        return true;
    }
}
