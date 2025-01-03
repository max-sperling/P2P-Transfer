#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "conf/IConf.hpp"

namespace conf::conf_json
{
    class ConfJson : public IConf
    {
    public:
        // --- IConf ------------------------------------------------------------------------------
        bool read(const view::ILoggerSPtr& logger, const std::filesystem::path& configPath, ConnectionDetails& conDetails) override;
        // ----------------------------------------------------------------------------------------
    };
}
