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
    TransferApp(const view::ViewType viewType, const conf::ConfType confType, const trans::TransType transType);

    bool exec(int argc, char *argv[]);

private:
    const view::ViewType m_viewType;
    const conf::ConfType m_confType;
    const trans::TransType m_transType;
};
