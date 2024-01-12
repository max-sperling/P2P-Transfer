#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "conf/IConfFwd.hpp"
#include <string>

class IConf
{
public:
    virtual ~IConf() {}

    /**
     * @param[out] det ... Connection details
     */
    virtual bool read(ConnectionDetails& det) = 0;
};

struct ConnectionDetails
{
    ConnectionDetails()
        : m_addr(""), m_port(0), m_dir("") {}

    ConnectionDetails(const std::string& addr, unsigned int port,
                      const std::string& dir)
        : m_addr(addr), m_port(port), m_dir(dir) {}

    std::string m_addr;
    unsigned int m_port;
    std::string m_dir;
};
