/************************/
/* Author: Max Sperling */
/************************/

#include "view/TestLogger.hpp"

#include <iostream>

using namespace std;

namespace view
{
    void TestLogger::logIt(const std::string& msg)
    {
        cout << msg << endl;
    }
}
