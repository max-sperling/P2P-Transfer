/************************/
/* Author: Max Sperling */
/************************/

#include "trans/TransTest.hpp"

#include "conf/IConf.hpp"
#include "trans/TestSerLis.hpp"
#include "trans/TransFactory.hpp"
#include "trans/TransTestUtils.hpp"
#include "trans/ITrans.hpp"
#include "view/TestLogger.hpp"

#include <QCoreApplication>
#include <QTimer>

#include <filesystem>
#include <fstream>

using namespace std;

namespace
{
    const filesystem::path testPath = "test_files";
    const filesystem::path testInputPath = testPath / "input";
    const filesystem::path testOutputPath = testPath / "output";
}

namespace trans
{
    TransTest::TransTest()
    {
        filesystem::create_directories(testInputPath);
    }

    TransTest::~TransTest()
    {
        filesystem::remove_all(testPath);
    }

    TEST_F(TransTest, testTransfer)
    {
        const string origFileName = "test_file.txt";
        const string origFileContent = "abcdef";
        const filesystem::path testInputFilePath = testInputPath / origFileName;

        ofstream ofs(testInputFilePath);
        ofs << origFileContent;
        ofs.close();

        int argc = 0;
        char** argv = nullptr;
        QCoreApplication app(argc, argv);
        string zipFileName;

        ITransSPtr trans = TransFactory::create(TransType::P2P);

        auto logger = make_shared<view::TestLogger>();
        auto conDet = make_shared<conf::ConnectionDetails>("127.0.0.1", 45450, testOutputPath);
        ASSERT_TRUE(trans->exec(logger, conDet));

        vector<string> testFilePaths{testInputFilePath};
        QTimer::singleShot(0, [&trans, &testFilePaths]() { trans->onSendTriggered(testFilePaths); });

        
        auto serLis = make_shared<TestSerLis>(app, zipFileName);
        trans->attach(serLis);
        app.exec();
        trans->detach(serLis);

        filesystem::path zipFilePath = testOutputPath / zipFileName;
        string destFileName;
        string destFileContent;
        ASSERT_TRUE(checkZipFile(zipFilePath, destFileName, destFileContent));

        EXPECT_EQ(destFileName, origFileName);
        EXPECT_EQ(destFileContent, origFileContent);
    }
}
