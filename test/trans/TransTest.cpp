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
#include <filesystem>
#include <iostream>
#include <fstream>

using namespace std;

namespace
{
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

TransTest::TransTest() {}

TransTest::~TransTest() {}

bool TransTest::exec(int argc, char *argv[])
{
    string fileName = "testfile.txt";
    string content = "abcdef";

    filesystem::path testPath = "testfiles";
    filesystem::path testInputPath = testPath / "input";
    filesystem::path testOutputPath = testPath / "output";
    filesystem::path testInputFilePath = testInputPath / fileName;
    filesystem::path testOutputFilePath = testOutputPath / fileName;

    // ----- Setup -----
    filesystem::create_directories(testInputPath);
    ofstream ofs(testInputFilePath);
    ofs << content;
    ofs.close();

    try
    {
        // ----- Run test -----
        QCoreApplication app(argc, argv);

        ConnectionDetails conDet("127.0.0.1", 45450, testOutputPath);

        shared_ptr<ViewDouble> view = make_shared<ViewDouble>();
        IConfSPtr conf = make_shared<ConfDouble>(conDet);
        ITransSPtr trans = TransFactory::create(TransType::P2P);

        if (!trans->init(view, conf)) throw;
        if (!trans->exec(argc, argv)) throw;

        QTimer::singleShot(0, [&view, &testInputFilePath]() {
            view->simulateSend(testInputFilePath);
        });

        ConLis conLis(&app);
        trans->attach(&conLis);
        app.exec();
        trans->detach(&conLis);

        // ----- Check result -----
        if (!filesystem::exists(testOutputFilePath)) throw;
        ifstream ifs(testOutputFilePath);
        stringstream buffer;
        buffer << ifs.rdbuf();
        ifs.close();

        if (buffer.str() == content)
        {
            cout << "Test successful" << endl;
        }
        else { throw; }
    }
    catch (...)
    {
        cout << "Test failed" << endl;
    }

    // ----- Cleanup -----
    filesystem::remove_all(testPath);

    return true;
}
