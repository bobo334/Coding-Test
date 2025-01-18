#include <iostream>
#include <windows.h>
#include "INIParser.hpp"
using namespace std;

int main()
{
        INIParser parser;

        const string filePath = "rdpwrap.ini";
        cout << "正在加载INI文件: " << filePath << endl;
        if (!parser.load(filePath)) {
            cout << "加载INI文件失败: " << filePath << endl;
            return 1;
        }

        string section = "10.0.22621.4655";

        unsigned int singleUserOffsetX64 = parser.getDWordHex(section, "SingleUserOffset.x64", 0x0);
        unsigned int defPolicyOffsetX64 = parser.getDWordHex(section, "DefPolicyOffset.x64", 0x0);

        if (parser.getBool(section, "SingleUserPatch.x64", "")) {
            cout << "SingleUserPatch.x64 is ture" << endl;
        }
        else {
            cout << "SingleUserPatch.x64 is false" << endl;
        }
        string defPolicyCodeX64 = parser.getString(section, "DefPolicyCode.x64", "");

        cout << "SingleUserOffset.x64: 0x" << hex << singleUserOffsetX64 << endl;
        cout << "DefPolicyOffset.x64: 0x" << hex << defPolicyOffsetX64 << endl;

        cout << "DefPolicyCode.x64: " << defPolicyCodeX64 << endl;
        stringstream ss;
        ss << "10.0.22621.4655" << "-SLInit";
        string section2 = ss.str();

        DWORD bInitialized_x64 = parser.getDWordHex(section2, "bInitialized.x64", 0x0);
        cout << "bInitialized.x64: 0x" << hex << bInitialized_x64 << endl;

    return 0;
}