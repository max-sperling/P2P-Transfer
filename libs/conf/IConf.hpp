#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "conf/IConfFwd.hpp"
#include "view/IViewFwd.hpp"

#include <filesystem>
#include <string>

namespace conf
{
    class IConf
    {
    public:
        virtual ~IConf() = default;

        /**
         * @param[in]  logger     ... Logger
         * @param[in]  configPath ... Path to the config
         * @param[out] conDetails ... Connection details
         */
        virtual bool read(const view::ILoggerSPtr& logger, const std::filesystem::path& configPath, ConnectionDetails& conDetails) = 0;
    };

    struct ConnectionDetails
    {
        ConnectionDetails() : m_addr("127.0.0.1"), m_port(45450), m_dir("files") {}

        ConnectionDetails(const std::string& addr, unsigned int port, const std::string& dir)
            : m_addr(addr), m_port(port), m_dir(dir) {}

        std::string m_addr;
        unsigned int m_port;
        std::string m_dir;
    };
}
