#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "view/IViewFwd.hpp"
#include "conf/IConfFwd.hpp"
#include "trans/ITransFwd.hpp"

class TransferApp
{
public:
    TransferApp(const ViewType viewType, const ConfType confType, const TransType transType);
    ~TransferApp();

    bool exec(int argc, char *argv[]);

private:
    const ViewType m_viewType;
    const ConfType m_confType;
    const TransType m_transType;
};
