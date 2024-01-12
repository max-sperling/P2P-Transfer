#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "conf/IConf.hpp"

class ConfJson : public IConf
{
public:
    ConfJson();
    ~ConfJson();

    // --- IConf -----------------------------
    bool read(ConnectionDetails& det) override;
    // ---------------------------------------
};
