/************************/
/* Author: Max Sperling */
/************************/

#include "TransferTest.hpp"
#include "trans/TransTest.hpp"

bool TransferTest::exec(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
