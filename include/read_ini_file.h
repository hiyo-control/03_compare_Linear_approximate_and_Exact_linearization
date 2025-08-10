#ifndef READ_INIFILE
#define READ_INIFILE

#include <iostream>
#include <string>
#include <map>

using namespace std;

class INIReader
{
public:
    bool load(const string& filename);
    string get(const string& section, const string& key) const;

private:
    map<string, string> data;
};

#endif
