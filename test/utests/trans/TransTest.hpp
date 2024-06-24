#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include <gtest/gtest.h>

namespace trans
{
    class TransTest : public testing::Test
    {
    protected:
        TransTest();
        ~TransTest() override;
    };
}
