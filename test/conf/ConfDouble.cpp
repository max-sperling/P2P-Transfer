/************************/
/* Author: Max Sperling */
/************************/

#include "ConfDouble.hpp"

ConfDouble::ConfDouble(const ConnectionDetails& det)
{
    m_conDet = det;
}

ConfDouble::~ConfDouble() {}

bool ConfDouble::read(ConnectionDetails& det)
{
    det = m_conDet;

    return true;
}
