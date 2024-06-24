/************************/
/* Author: Max Sperling */
/************************/

#include "ConfDouble.hpp"

namespace conf
{
    ConfDouble::ConfDouble(const ConnectionDetails& det)
    {
        m_conDet = det;
    }

    bool ConfDouble::read(ConnectionDetails& det)
    {
        det = m_conDet;

        return true;
    }
}
