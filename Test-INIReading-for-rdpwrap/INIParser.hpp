#ifndef INIPARSER_HPP
#define INIPARSER_HPP

#include <string>
#include <bitset>
#include <unordered_map>
#include <sstream>
#include <stdexcept>
#include <cstring>
#include "ini.h"
using namespace std;

class INIParser
{
private:
    unordered_map<string, unordered_map<string, string>> data;

    static int iniHandler(void *user, const char *section, const char *name, const char *value)
    {
        INIParser *parser = static_cast<INIParser *>(user);
        parser->data[section][name] = value;
        return 1;
    }

public:
    bool load(const string &filePath)
    {
        if (ini_parse(filePath.c_str(), iniHandler, this) < 0)
        {
            return false;
        }
        return true;
    }

    unsigned int getDWordHex(const string &section, const string &name, unsigned int defaultValue = 0)
    {
        string value = getString(section, name, "");
        if (value.empty())
            return defaultValue;

        try
        {
            return stoul(value, nullptr, 16);
        }
        catch (const exception &)
        {
            return defaultValue;
        }
    }

    string getString(const string &section, const string &name, const string &defaultValue = "")
    {
        if (data.find(section) != data.end() && data[section].find(name) != data[section].end())
        {
            return data[section][name];
        }
        return defaultValue;
    }

    bool getBool(const string &section, const string &name, bool defaultValue = false)
    {
        string value = getString(section, name, "");
        if (value.empty())
            return defaultValue;
        return (value == "true" || value == "1" || value == "yes");
    }

    int getInt(const string &section, const string &name, int defaultValue = 0)
    {
        string value = getString(section, name, "");
        if (value.empty())
            return defaultValue;
        return stoi(value);
    }

    string getHex(const string &section, const string &name, const string &defaultValue = "0x0")
    {
        string value = getString(section, name, defaultValue);
        if (value.empty())
            return defaultValue;

        if (value.size() >= 2 && value[0] == '0' && (value[1] == 'x' || value[1] == 'X'))
        {
            return value;
        }

        return "0x" + value;
    }

    string getBinary(const string &section, const string &name, int defaultValue = 0)
    {
        int value = getInt(section, name, defaultValue);
        stringstream ss;
        ss << "0b" << bitset<32>(value).to_string();
        return ss.str();
    }
};

#endif // INIPARSER_HPP