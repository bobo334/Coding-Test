#include <iostream>
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

        string section = "6.0.6000.16386";

        unsigned int singleUserOffsetX86 = parser.getDWordHex(section, "SingleUserOffset.x86", 0x0);
        unsigned int singleUserOffsetX64 = parser.getDWordHex(section, "SingleUserOffset.x64", 0x0);
        unsigned int defPolicyOffsetX86 = parser.getDWordHex(section, "DefPolicyOffset.x86", 0x0);
        unsigned int defPolicyOffsetX64 = parser.getDWordHex(section, "DefPolicyOffset.x64", 0x0);

        string singleUserCodeX86 = parser.getString(section, "SingleUserCode.x86", "");
        string singleUserCodeX64 = parser.getString(section, "SingleUserCode.x64", "");
        string defPolicyCodeX86 = parser.getString(section, "DefPolicyCode.x86", "");
        string defPolicyCodeX64 = parser.getString(section, "DefPolicyCode.x64", "");

        cout << "SingleUserOffset.x86: 0x" << hex << singleUserOffsetX86 << endl;
        cout << "SingleUserOffset.x64: 0x" << hex << singleUserOffsetX64 << endl;
        cout << "DefPolicyOffset.x86: 0x" << hex << defPolicyOffsetX86 << endl;
        cout << "DefPolicyOffset.x64: 0x" << hex << defPolicyOffsetX64 << endl;

        cout << "SingleUserCode.x86: " << singleUserCodeX86 << endl;
        cout << "SingleUserCode.x64: " << singleUserCodeX64 << endl;
        cout << "DefPolicyCode.x86: " << defPolicyCodeX86 << endl;
        cout << "DefPolicyCode.x64: " << defPolicyCodeX64 << endl;

    return 0;
}