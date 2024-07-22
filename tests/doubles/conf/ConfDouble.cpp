/************************/
/* Author: Max Sperling */
/************************/

#include "ConfDouble.hpp"

namespace conf
{
    bool ConfDouble::read(const std::filesystem::path& configPath, ConnectionDetails& conDetails)
    {
        m_conDet = conDetails;

        return true;
    }
}
