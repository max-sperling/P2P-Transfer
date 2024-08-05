#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "view/IView.hpp"
#include "trans/ITransFwd.hpp"
#include "conf/IConfFwd.hpp"

#include <archive.h>
#include <archive_entry.h>
#include <QThread>
#include <QTcpSocket>
#include <filesystem>
#include <fstream>
#include <memory>
#include <string>
#include <unordered_map>

namespace trans::trans_p2p
{
    struct InputClientData
    {
        QByteArray m_dataBuffer{};
        ssize_t m_currentPos{};
    };

    enum class State
    {
        readHeader,
        readFile,
        reachedEOF,
        waitForData,
        errorState
    };

    class Input : public QThread
    {
        Q_OBJECT

    public:
        Input(const view::IViewSPtr& view, const std::shared_ptr<conf::ConnectionDetails>& det,
              const std::shared_ptr<IConLisVec>& lis, qintptr socketId);
        ~Input() override;

    protected:
        void run() override;

    private:
        bool readHeader();
        bool readFile();
        bool updateState(int input);

        static ssize_t myread(struct archive *a, void *client_data, const void **buff);
        static int myopen(struct archive *a, void *client_data);
        static int myclose(struct archive *a, void *client_data);

        view::IViewSPtr m_view;
        std::string m_logIdent;

        std::shared_ptr<conf::ConnectionDetails> m_conDet;
        std::shared_ptr<IConLisVec> m_conLis;

        QTcpSocket* m_socket;
        qintptr m_socketId;

        archive* m_archive;
        archive_entry* m_entry;

        InputClientData m_clientData;
        State m_archiveState;
        std::filesystem::path m_outputPath;
        std::filesystem::path m_currentOutputPath;

    private slots:
        void onReceivedData();
        void onDisconnected();
    };
}
