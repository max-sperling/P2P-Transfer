/************************/
/* Author: Max Sperling */
/************************/

#include "view/ViewFactory.hpp"
#include "view/view_qt/ViewQt.hpp"
#include <memory>

using namespace std;

IViewSPtr ViewFactory::create(const ViewType type)
{
    IViewSPtr viewPtr;

    switch (type)
    {
    case ViewType::Qute:
        viewPtr = make_shared<ViewQt>();
        break;
    }

    return viewPtr;
}
