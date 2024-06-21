/************************/
/* Author: Max Sperling */
/************************/

#include "view/ViewDouble.hpp"
// #include <iostream>

using namespace std;

bool ViewDouble::start()
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

void ViewDouble::simulateSend(const string& file)
{
    for (IViewListener* lis : m_viewLis)
    {
        lis->onSendTriggered(file);
    }
}
