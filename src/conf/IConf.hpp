#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "conf/IConfFwd.hpp"

#include <filesystem>
#include <string>

namespace conf
{
    class IConf
    {
    public:
        virtual ~IConf() = default;

        /**
         * @param[in]  configPath ... Path to the config
         * @param[out] conDetails ... Connection details
         */
        virtual bool read(const std::filesystem::path& configPath, ConnectionDetails& conDetails) = 0;
    };

    struct ConnectionDetails
    {
        ConnectionDetails() = default;

        ConnectionDetails(const std::string& addr, unsigned int port, const std::string& dir)
            : m_addr(addr), m_port(port), m_dir(dir) {}

        std::string m_addr{"127.0.0.1"};
        unsigned int m_port{45450};
        std::string m_dir{"files"};
    };
}
