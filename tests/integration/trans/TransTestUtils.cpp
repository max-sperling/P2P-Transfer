/************************/
/* Author: Max Sperling */
/************************/

#include "trans/TransTestUtils.hpp"

#include <archive.h>
#include <archive_entry.h>

#include <iostream>

using namespace std;

namespace trans
{
    bool checkZipFile(const std::filesystem::path& zipFilePath, std::string& fileName, std::string& fileContent)
    {
        fileName.clear();
        fileContent.clear();

        if (!std::filesystem::exists(zipFilePath))
        {
            cerr << "The provided zip file path does not exist" << endl;
            return false;
        }

        archive* archive = archive_read_new();
        if (!archive)
        {
            cerr << "Can't create the zip archive reader." << endl;
            return false;
        }

        archive_read_support_format_zip(archive);

        if (archive_read_open_filename(archive, zipFilePath.c_str(), 10240) != ARCHIVE_OK)
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
