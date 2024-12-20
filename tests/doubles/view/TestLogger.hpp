#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "view/IView.hpp"

#include <string>

namespace view
{
    class TestLogger : public view::ILogger
    {
    public:
        // --- ILogger ---------------------------
        void logIt(const std::string& msg) override;
        // ---------------------------------------
    };
}
