#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "view/IViewFwd.hpp"

#include <archive.h>
#include <QTcpSocket>

#include <filesystem>

namespace trans::trans_p2p
{
    struct ClientData
    {
        ClientData() = delete;
        ClientData(view::IViewSPtr view, const std::string& logIdent, QTcpSocket* socket);

        view::IViewSPtr m_view;
        const std::string& m_logIdent;
        QTcpSocket* m_socket;
    };

    class Streamer
    {
    public:
        Streamer(view::IViewSPtr view, const std::string& logIdent, QTcpSocket* socket);

        bool streamItems(std::vector<std::string>& items);

    private:
        bool streamItem(const std::filesystem::path& item, const std::filesystem::path& basePath);
        bool streamDir(const std::filesystem::path& dirPath, const std::filesystem::path& basePath) const;
        bool streamFile(const std::filesystem::path& filePath, const std::filesystem::path& basePath) const;

        view::IViewSPtr m_view;
        const std::string& m_logIdent;

        ClientData m_clientData;
        archive* m_archive;
    };
}
