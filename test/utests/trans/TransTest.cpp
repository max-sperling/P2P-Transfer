/************************/
/* Author: Max Sperling */
/************************/

#include "trans/TransTest.hpp"
#include "trans/TransFactory.hpp"
#include "trans/ITrans.hpp"
#include "conf/IConfFwd.hpp"
#include "conf/ConfDouble.hpp"
#include "view/IViewFwd.hpp"
#include "view/ViewDouble.hpp"
#include <QCoreApplication>
#include <QTimer>
#include <iostream>
#include <filesystem>
#include <fstream>

using namespace std;

namespace
{
    const std::filesystem::path testPath = "test_files";
    const std::filesystem::path testInputPath = testPath / "input";
    const std::filesystem::path testOutputPath = testPath / "output";

    class ConLis : public IConnectionListener
    {
    public:
        ConLis(QCoreApplication* app) : m_app(app) {}

        virtual void onConnectionStarted(const string& file,
            const IConnectionListener::ConnectionType type) {}

        virtual void onConnectionFinished(const string& file,
            const IConnectionListener::ConnectionType type)
        {
            if (type == IConnectionListener::ConnectionType::INCOMING)
            {
                m_app->quit();
            }
        }
    private:
        QCoreApplication* m_app;
    };
}

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
    const std::string fileName = "test_file_1.txt";
    const std::filesystem::path testInputFilePath = testInputPath / fileName;
    const std::filesystem::path testOutputFilePath = testOutputPath / fileName;
    const std::string content = "abcdef";

    ofstream ofs(testInputFilePath);
    ofs << content;
    ofs.close();

    int argc = 0;
    char** argv = nullptr;
    QCoreApplication app(argc, argv);

    ConnectionDetails conDet("127.0.0.1", 45450, testOutputPath);

    shared_ptr<ViewDouble> view = make_shared<ViewDouble>();
    IConfSPtr conf = make_shared<ConfDouble>(conDet);
    ITransSPtr trans = TransFactory::create(TransType::P2P);

    ASSERT_EQ(trans->init(view, conf), true);
    ASSERT_EQ(trans->exec(), true);

    QTimer::singleShot(0, [&view, &testInputFilePath]() {
        view->simulateSend(testInputFilePath);
    });

    ConLis conLis(&app);
    trans->attach(&conLis);
    app.exec();
    trans->detach(&conLis);

    ASSERT_EQ(filesystem::exists(testOutputFilePath), true);

    ifstream ifs(testOutputFilePath);
    stringstream buffer;
    buffer << ifs.rdbuf();
    ifs.close();

    EXPECT_EQ(buffer.str(), content);
}
