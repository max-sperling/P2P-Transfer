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
