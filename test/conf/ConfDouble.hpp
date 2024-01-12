#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "conf/IConf.hpp"

class ConfDouble : public IConf
{
public:
    /**
     * @param[in] det ... Connection details
     */
    ConfDouble(const ConnectionDetails& det);
    ~ConfDouble();

    // --- IConf -----------------------------
    bool read(ConnectionDetails& det) override;
    // ---------------------------------------

private:
    ConnectionDetails m_conDet;
};
