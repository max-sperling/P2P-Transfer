/************************/
/* Author: Max Sperling */
/************************/

#include "conf/conf_json/JsonParser.hpp"

using namespace std;

namespace conf::conf_json
{
    JsonParser::JsonParser()
    {
        resetParser();
    }

    JsonParser::~JsonParser()
    {
        resetParser();
    }

    void JsonParser::parseFile(const std::filesystem::path& filePath)
    {
        resetParser();

        m_file.open(filePath);
        if (!m_file.is_open()) throw;

        char c;
        while (!m_file.eof())
        {
            m_file.get(c);
            changeState(c);
        }

        m_file.close();
    }

    void JsonParser::getValStr(const string& name, string& value)
    {
        auto iter = m_data.find(name);
        if (iter == m_data.end()) throw;
        if (iter->second.type != Data::Types::text) throw;
        value = iter->second.value;
    }

    void JsonParser::getValInt(const string& name, unsigned int& value)
    {
        auto iter = m_data.find(name);
        if (iter == m_data.end()) throw;
        if (iter->second.type != Data::Types::number) throw;
        value = stoi(iter->second.value);
    }

    void JsonParser::resetParser()
    {
        if (m_file.is_open()) { m_file.close(); }

        m_state = States::start;
        m_ident = "";
        m_value = "";
        m_data.clear();
    }

    void JsonParser::changeState(char input)
    {
        switch (input)
        {
            case '\r':
            case '\n':
            case '\t':
            case ' ':
            case '{':
            case ':':
                break;
            case '"':
                switch (m_state)
                {
                    case States::start:
                        m_state = States::name;
                        break;
                    case States::equals:
                        m_state = States::text;
                        break;
                    case States::name:
                        m_state = States::equals;
                        break;
                    case States::text:
                        {
                            Data data;
                            data.type = Data::Types::text;
                            data.value = m_value;
                            m_data.insert(pair<string, Data>(m_ident, data));
                        }
                        m_state = States::start;
                        m_ident = "";
                        m_value = "";
                        break;
                    default:
                        break;
                }
                break;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                switch (m_state)
                {
                    case States::name:
                        m_ident += input;
                        break;
                    case States::equals:
                        m_state = States::number;
                    case States::text:
                    case States::number:
                        m_value += input;
                        break;
                    default:
                        break;
                }
                break;
            case '}':
            case ',':
                switch (m_state)
                {
                    case States::number:
                        {
                            Data data;
                            data.type = Data::Types::number;
                            data.value = m_value;
                            m_data.insert(pair<string, Data>(m_ident, data));
                        }
                        m_state = States::start;
                        m_ident = "";
                        m_value = "";
                        break;
                    default:
                        break;
                }
                break;
            default:
                switch (m_state)
                {
                    case States::name:
                        m_ident += input;
                        break;
                    case States::text:
                        m_value += input;
                        break;
                    default:
                        break;
                }
                break;
        }
    }
}
