/************************/
/* Author: Max Sperling */
/************************/

#include "trans/trans_p2p/Input.hpp"

#include "trans/trans_p2p/TransP2P.hpp"
#include "trans/ITrans.hpp"
#include "conf/IConf.hpp"

#include <QBuffer>
#include <QDir>
#include <fstream>
#include <iostream>

using namespace std;

namespace trans::trans_p2p
{
    // ***** Public ************************************************************************************
    Input::Input(const view::IViewSPtr& view, const shared_ptr<conf::ConnectionDetails>& det,
                 const shared_ptr<IConLisVec>& lis, qintptr socketId)
    {
        m_view = view;
        m_conDet = det;
        m_conLis = lis;
        m_logIdent = "[Server][" + to_string(socketId) + "]";
        m_socket = nullptr;
        m_socketId = socketId;
    }

    Input::~Input()
    {
        for (IConnectionListener* lis : *m_conLis)
        {
            lis->onConnectionFinished(m_socketId, IConnectionListener::ConnectionType::INCOMING);
        }
    }
    // *************************************************************************************************

    // ***** Protected *********************************************************************************
    void Input::run()
    {
        m_socket = new QTcpSocket();
        // m_socket->setSocketOption(QAbstractSocket::ReceiveBufferSizeSocketOption, QVariant::fromValue(max_packet_payload_size));

        if (!m_socket->setSocketDescriptor(m_socketId))
        {
            m_view->logIt(m_logIdent + " Can't setup socket");
            return;
        }

        connect(m_socket, SIGNAL(readyRead()), this, SLOT(onReceivedData()));
        connect(m_socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));

        m_view->logIt(m_logIdent + " Connected");

        exec();
    }
    // *************************************************************************************************

    // ***** Slots *************************************************************************************
    void Input::onReceivedData()
    {
        while (m_socket->bytesAvailable())
        {
            m_receivedData.append(m_socket->readAll());
        }
    }

    void Input::onDisconnected()
    {
        m_view->logIt(m_logIdent + " Disconnected");

        if (!m_receivedData.isEmpty())
        {
            const auto outputPath = std::filesystem::current_path() / m_conDet->m_dir / to_string(m_socketId);
            create_directories(outputPath);
            for (const auto& item : std::filesystem::directory_iterator(outputPath))
            {
                remove_all(item);
            }

            unzipFileFromMemory(m_receivedData, outputPath);
            m_receivedData.clear();
        }

        m_socket->close();
        quit();
    }

    void Input::unzipFileFromMemory(const QByteArray& receivedData, const std::filesystem::path& outputFolder)
    {
        archive* archive = archive_read_new();
        archive_read_support_format_zip(archive);
        archive_read_support_filter_all(archive);

        int r = archive_read_open_memory(archive, receivedData.constData(), receivedData.size());
        if (r != ARCHIVE_OK) {
            std::cerr << "Error opening archive: " << archive_error_string(archive) << std::endl;
            archive_read_free(archive);
            return;
        }

        archive_entry* entry;
        while (true)
        {
            r = archive_read_next_header(archive, &entry);
            if (r == ARCHIVE_EOF) {
                std::cout << "Reached end of file" << std::endl;
                break;
            }
            if (r < ARCHIVE_WARN) {
                std::cerr << "Warning reading header: " << archive_error_string(archive) << std::endl;
                break;
            }
            if (r < ARCHIVE_OK) {
                std::cerr << "Error reading header: " << archive_error_string(archive) << std::endl;
                break;
            }

            std::filesystem::path outputPath = outputFolder / archive_entry_pathname(entry);
            archive_entry_set_pathname(entry, outputPath.string().c_str());

            r = archive_read_extract(archive, entry, ARCHIVE_EXTRACT_PERM | ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_ACL | ARCHIVE_EXTRACT_FFLAGS);
            if (r < ARCHIVE_WARN) {
                std::cerr << "Warning extracting file: " << archive_error_string(archive) << std::endl;
            } else if (r < ARCHIVE_OK) {
                std::cerr << "Error extracting file: " << archive_error_string(archive) << std::endl;
            }
        }

        archive_write_close(archive);
        archive_read_free(archive);
    }
    // *************************************************************************************************
}
