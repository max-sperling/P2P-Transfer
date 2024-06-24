/************************/
/* Author: Max Sperling */
/************************/

#include "TransferApp.hpp"
#include "view/IViewFwd.hpp"
#include "conf/IConfFwd.hpp"
#include "trans/ITransFwd.hpp"

int main(int argc, char *argv[])
{
    TransferApp transApp(view::ViewType::Qute, conf::ConfType::Json, trans::TransType::P2P);
    transApp.exec(argc, argv);

    return 0;
}
