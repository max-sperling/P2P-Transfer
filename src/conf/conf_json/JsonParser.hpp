#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include <string>
#include <map>
#include <fstream>

#include <filesystem>

namespace conf
{
    namespace conf_json
    {
        class JsonParser
        {
        public:
            JsonParser();
            ~JsonParser();

            /**
             * @param[in] filePath ... File path
             */
            void parseFile(const std::filesystem::path& filePath);

            /**
             * @param[in]  name  ... Name
             * @param[out] value ... Value
             */
            void getValStr(const std::string& name, std::string& value);

            /**
             * @param[in]  name  ... Name
             * @param[out] value ... Value
             */
            void getValInt(const std::string& name, unsigned int& value);

        private:
            void resetParser();
            void changeState(char input);

            enum States
            {
                start, equals, name, number, text, error
            };

            struct Data
            {
                enum Types { text, number };
                Types type;
                std::string value;
            };

            std::fstream m_file;

            States m_state;
            std::string m_ident;
            std::string m_value;
            std::map<std::string, Data> m_data;
        };
    }
}
