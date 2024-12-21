#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include <filesystem>
#include <string>

namespace trans
{
    /**
     * @param[in]  zipFilePath ... Path to the zip file
     * @param[out] fileName    ... Name of the file in the zip
     * @param[out] fileContent ... Content of the file in the zip
     */
    bool checkZipFile(const std::filesystem::path& zipFilePath, std::string& fileName, std::string& fileContent);
}
