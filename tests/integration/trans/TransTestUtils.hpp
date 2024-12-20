#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include <filesystem>
#include <string>

namespace trans
{
    bool checkZipFileExistance(const std::filesystem::path& outputPath, std::string& zipFileName);
    bool checkZipFileContent(const std::string& zipFileName, std::string& fileName, std::string& fileContent);
}
