/************************/
/* Author: Max Sperling */
/************************/

#include "trans/TransTest.hpp"

#include "conf/IConf.hpp"
#include "trans/TransFactory.hpp"
#include "trans/ITrans.hpp"
#include "view/ViewDouble.hpp"

#include <archive.h>
#include <archive_entry.h>
#include <QCoreApplication>
#include <QTimer>

#include <filesystem>
#include <fstream>
#include <iostream>

using namespace std;

namespace
{
    const filesystem::path testPath = "test_files";
    const filesystem::path testInputPath = testPath / "input";
    const filesystem::path testOutputPath = testPath / "output";

    class ConLis : public trans::IConnectionListener
    {
    public:
        ConLis(QCoreApplication* app) : m_app(app) {}

        void onConnectionStarted(long long socketId, IConnectionListener::ConnectionType type) override {}

        void onConnectionFinished(long long socketId, IConnectionListener::ConnectionType type) override
        {
            if (type == IConnectionListener::ConnectionType::INCOMING)
            {
                m_app->quit();
            }
        }
    private:
        QCoreApplication* m_app;
    };

    bool checkZipFileExistance(const filesystem::path& outputPath, string& zipFileName)
    {
        zipFileName.clear();

        for (const auto& entry : filesystem::directory_iterator(outputPath))
        {
            if (entry.path().extension() == ".zip")
            {
                if (!zipFileName.empty())
                {
                    cerr << "More than one zip file found in the folder." << endl;
                    return false;
                }
                zipFileName = entry.path().string();
            }
        }
        if (zipFileName.empty())
        {
            cerr << "No zip file found in the folder." << endl;
            return false;
        }

        return true;
    }

    bool checkZipFileContent(const string& zipFileName, string& fileName, string& fileContent)
    {
        fileName.clear();
        fileContent.clear();

        archive* archive = archive_read_new();
        if (!archive)
        {
            cerr << "Can't create the zip archive reader." << endl;
            return false;
        }

        archive_read_support_format_zip(archive);

        if (archive_read_open_filename(archive, zipFileName.c_str(), 10240) != ARCHIVE_OK)
        {
            cerr << "Can't open the zip archive for reading." << endl;
            return false;
        }

        archive_entry* entry{};
        unsigned file_count{};

        while (archive_read_next_header(archive, &entry) == ARCHIVE_OK)
        {
            if (++file_count > 1)
            {
                cerr << "The zip file contains more than one file." << endl;
                return false;
            }

            fileName = archive_entry_pathname(entry);
            size_t size = archive_entry_size(entry);

            string buffer(size, '\0');
            if (archive_read_data(archive, buffer.data(), size) != static_cast<ssize_t>(size))
            {
                cerr << "Error while reading the zip archive data." << endl;
                return false;
            }
            fileContent = buffer;
        }

        archive_read_close(archive);
        archive_read_free(archive);

        return true;
    }
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

        ITransSPtr trans = TransFactory::create(TransType::P2P);

        auto view = make_shared<view::ViewDouble>();
        auto conDet = make_shared<conf::ConnectionDetails>("127.0.0.1", 45450, testOutputPath);
        ASSERT_TRUE(trans->exec(view, conDet));

        vector<string> testFilePaths{testInputFilePath};
        QTimer::singleShot(0, [&view, &testFilePaths]() { view->simulateSend(testFilePaths); });

        ConLis conLis(&app);
        trans->attach(&conLis);
        app.exec();
        trans->detach(&conLis);

        string zipFileName;
        ASSERT_TRUE(checkZipFileExistance(testOutputPath, zipFileName));

        string destFileName;
        string destFileContent;
        ASSERT_TRUE(checkZipFileContent(zipFileName, destFileName, destFileContent));

        EXPECT_EQ(destFileName, origFileName);
        EXPECT_EQ(destFileContent, origFileContent);
    }
}
