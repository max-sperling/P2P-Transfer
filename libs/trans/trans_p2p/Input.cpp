/************************/
/* Author: Max Sperling */
/************************/

#include "trans/trans_p2p/Input.hpp"

#include <archive_entry.h>

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
        m_archive = nullptr;
        m_archiveState = State::readHeader;
        m_outputPath = std::filesystem::current_path() / m_conDet->m_dir / to_string(m_socketId);
    }

    Input::~Input()
    {
        for (IConnectionListener* lis : *m_conLis)
        {
            lis->onConnectionFinished(m_socketId, IConnectionListener::ConnectionType::INCOMING);
        }

        if (m_archive)
        {
            archive_read_free(m_archive);
        }

        m_clientData.m_dataBuffer.clear();
        m_clientData.m_currentPos = 0;
    }
    // *************************************************************************************************

    ssize_t Input::myread(struct archive *a, void *client_data, const void **buff)
    {
        auto* mydata = static_cast<InputClientData*>(client_data);

        *buff = mydata->m_dataBuffer.data() + mydata->m_currentPos;

        ssize_t len = mydata->m_dataBuffer.size() - mydata->m_currentPos;
        mydata->m_currentPos = mydata->m_dataBuffer.size();

        return len;
    }

    int Input::myopen(struct archive *a, void *client_data)
    {
        return ARCHIVE_OK;
    }

    int Input::myclose(struct archive *a, void *client_data)
    {
        return ARCHIVE_OK;
    }

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

        if (!exists(m_outputPath))
        {
            create_directories(m_outputPath);
        }

        exec();
    }
    // *************************************************************************************************

    // ***** Slots *************************************************************************************
    void Input::onReceivedData()
    {
        while (m_socket->bytesAvailable())
        {
            m_clientData.m_dataBuffer.append(m_socket->readAll());
            m_view->logIt(m_logIdent + " Buffer size: " + to_string(m_clientData.m_dataBuffer.size()) + " bytes");

            if (!m_archive)
            {
                m_archive = archive_read_new();
                archive_read_support_format_zip(m_archive);
                archive_read_support_filter_all(m_archive);

                if (archive_read_open(m_archive, &m_clientData, myopen, myread, myclose) != ARCHIVE_OK)
                {
                    std::cerr << "Failed to initialize libarchive." << std::endl;
                }
            }

            bool ret = true;
            while (ret)
            {
                switch (m_archiveState)
                {
                    case State::readHeader:
                        ret = readHeader();
                    break;
                    case State::readFile:
                        ret = readFile();
                    break;
                    default:
                        return;
                }
            }
        }
    }

    bool Input::readHeader()
    {
        m_entry = archive_entry_new();

        int res = archive_read_next_header(m_archive, &m_entry);

        bool ret = updateState(res);
        if (ret)
        {
            m_currentOutputPath = m_outputPath / archive_entry_pathname(m_entry);
            archive_entry_set_pathname(m_entry, m_currentOutputPath.string().c_str());
            m_view->logIt(m_logIdent + " Writing file: " + archive_entry_pathname(m_entry));
        }

        return ret;
    }

    bool Input::readFile()
    {
        //int r = archive_read_data_skip(m_archive);
        int res = archive_read_extract(m_archive, m_entry, ARCHIVE_EXTRACT_PERM | ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_ACL | ARCHIVE_EXTRACT_FFLAGS);

        return updateState(res);
    }

    void Input::onDisconnected()
    {
        m_view->logIt(m_logIdent + " Disconnected");

        m_socket->close();
        quit();
    }
    // *************************************************************************************************

    // ***** Private ***********************************************************************************
    bool Input::updateState(int input)
    {
        switch (input)
        {
            case ARCHIVE_EOF: {
                std::cout << "Archive EOF" << std::endl;
                m_archiveState = State::reachedEOF;
                return false;
            }
            case ARCHIVE_OK: {
                std::cout << "Archive OK" << std::endl;
                if (m_archiveState == State::readHeader) m_archiveState = State::readFile;
                else if (m_archiveState == State::readFile) m_archiveState = State::readHeader;
                break;
            }
            case ARCHIVE_RETRY: {
                std::cout << "Archive retry" << std::endl;
                return false;
            }
            case ARCHIVE_WARN:
            case ARCHIVE_FAILED:
            case ARCHIVE_FATAL: {
                std::cout << "Archive error: " << archive_error_string(m_archive) << std::endl;
                m_archiveState = State::errorState;
                return false;
            }
        }
        return true;
    }
    // *************************************************************************************************
}
