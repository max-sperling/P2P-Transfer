#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "conf/IConf.hpp"

namespace conf
{
    namespace conf_json
    {
        class ConfJson : public IConf
        {
        public:
            // --- IConf -----------------------------
            bool read(ConnectionDetails& det) override;
            // ---------------------------------------
        };
    }
}
