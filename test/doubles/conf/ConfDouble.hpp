#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "conf/IConf.hpp"

namespace conf
{
    class ConfDouble : public IConf
    {
    public:
        // --- IConf -----------------------------
        bool read(const std::filesystem::path& configPath, ConnectionDetails& conDetails) override;
        // ---------------------------------------

    private:
        ConnectionDetails m_conDet;
    };
}
