/************************/
/* Author: Max Sperling */
/************************/

#include "trans/trans_p2p/Streamer.hpp"

#include "view/IView.hpp"

#include <archive.h>
#include <archive_entry.h>

#include <array>
#include <filesystem>
#include <fstream>

namespace
{
    constexpr size_t packet_payload_size = 4 * 1024 * 1024; // 4 MiB
    constexpr size_t max_fread_buffer_size = 10 * 1024 * 1024; // 10 MiB

    int memory_write_open(archive* /*archive*/, void* /*client_data*/)
    {
        return ARCHIVE_OK;
    }

    la_ssize_t memory_write(archive* /*archive*/, void* client_data, const void* buff, size_t length)
    {
        auto* clientData = static_cast<trans::trans_p2p::ClientData*>(client_data);

        clientData->m_view->logIt(clientData->m_logIdent + " Send packet with " + std::to_string(length) + " bytes");

        clientData->m_socket->write(static_cast<const char*>(buff), length);
        clientData->m_socket->flush();

        return length;
    }

    int memory_write_close(archive* /*archive*/, void* /*client_data*/)
    {
        return ARCHIVE_OK;
    }
}

namespace trans::trans_p2p
{
    ClientData::ClientData(view::IViewSPtr view, const std::string& logIdent, QTcpSocket* socket)
        : m_view(view), m_logIdent(logIdent), m_socket(socket) {}

    Streamer::Streamer(view::IViewSPtr view, const std::string& logIdent, QTcpSocket* socket)
        : m_view(view), m_logIdent(logIdent), m_clientData({view, logIdent, socket}), m_archive(nullptr) {}

    bool Streamer::streamItems(std::vector<std::string>& items)
    {
        m_archive = archive_write_new();
        archive_write_set_format_zip(m_archive);
        archive_write_set_bytes_per_block(m_archive, packet_payload_size);
        archive_write_open(m_archive, &m_clientData, memory_write_open, memory_write, memory_write_close);

        for (const auto& item : items)
        {
            std::string basePath = static_cast<std::filesystem::path>(item).parent_path();
            streamItem(item, basePath);
        }

        archive_write_close(m_archive);
        archive_write_free(m_archive);

        return true;
    }

    bool Streamer::streamItem(const std::filesystem::path& item, const std::filesystem::path& basePath)
    {
        if (is_directory(item))
        {
            streamDir(item, basePath);
            for (auto& subItem : std::filesystem::directory_iterator(item))
            {
                streamItem(subItem, basePath);
            }
        }
        else if (is_regular_file(item))
        {
            streamFile(item, basePath);
        }
        else
        {
            // Ignore other files
        }

        return true;
    }

    bool Streamer::streamFile(const std::filesystem::path& filePath, const std::filesystem::path& basePath) const
    {
        std::ifstream file(filePath, std::ios::binary);
        if (!file.is_open()) { return false; }

        std::string relPath = relative(filePath, basePath).string();

        archive_entry* entry = archive_entry_new();
        archive_entry_set_pathname(entry, relPath.c_str());
        archive_entry_set_size(entry, file_size(filePath));
        archive_entry_set_filetype(entry, S_IFREG);
        archive_entry_set_perm(entry, 0644);
        archive_write_header(m_archive, entry);

        size_t bytesRead{};
        auto buffer = std::make_unique<std::array<char, max_fread_buffer_size>>();
        while ((bytesRead = file.read(buffer->data(), buffer->size()).gcount()) > 0)
        {
            archive_write_data(m_archive, buffer->data(), bytesRead);
        }

        archive_entry_free(entry);
        return true;
    }

    bool Streamer::streamDir(const std::filesystem::path& dirPath, const std::filesystem::path& basePath) const
    {
        std::string relPath = relative(dirPath, basePath).string();

        archive_entry* entry = archive_entry_new();
        archive_entry_set_pathname(entry, relPath.c_str());
        archive_entry_set_size(entry, 0);
        archive_entry_set_filetype(entry, S_IFDIR);
        archive_entry_set_perm(entry, 0644);
        archive_write_header(m_archive, entry);

        return true;
    }
}
