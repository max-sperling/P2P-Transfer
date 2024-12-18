/************************/
/* Author: Max Sperling */
/************************/

#include "view/ViewDouble.hpp"

// #include <iostream>

using namespace std;

namespace view
{
    bool ViewDouble::exec()
    {
        return true;
    }

    void ViewDouble::logIt(const string& msg)
    {
        // cout << str << endl;
    }

    bool ViewDouble::attach(IViewListener* lis)
    {
        m_viewLis.push_back(lis);

        return true;
    }

    bool ViewDouble::detach(IViewListener* /*lis*/)
    {
        return true;
    }

    void ViewDouble::simulateSend(const vector<string>& files)
    {
        for (IViewListener* lis : m_viewLis)
        {
            lis->onSendTriggered(files);
        }
    }
}
