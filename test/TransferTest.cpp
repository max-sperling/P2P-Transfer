/************************/
/* Author: Max Sperling */
/************************/

#include "TransferTest.hpp"
#include "trans/TransTest.hpp"

TransferTest::TransferTest() {}

TransferTest::~TransferTest() {}

bool TransferTest::exec(int argc, char *argv[])
{
    TransTest transTest;
    transTest.exec(argc, argv);

    return true;
}
