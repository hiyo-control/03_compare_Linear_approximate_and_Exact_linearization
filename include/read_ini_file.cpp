#include "read_ini_file.h"
#include <fstream>
#include <sstream>

bool INIReader::load(const string& filename) {
    ifstream file(filename);
    if (!file.is_open())
    {
        return false;
    }

    string line, currentSection;
    while (getline(file, line))
    {
        if (line.empty() || line[0] == ';' || line[0] == '#')
        {
            continue;
        }

        if (line.front() == '[' && line.back() == ']')
        {
            currentSection = line.substr(1, line.size() - 2);
        }
        else
        {
            istringstream ss(line);
            string key, value;
            if (getline(ss, key, '=') && getline(ss, value))
            {
                data[currentSection + "." + key] = value;
            }
        }
    }

    return true;
}

string INIReader::get(const string& section, const string& key) const
{
    auto it = data.find(section + "." + key);
    return (it != data.end()) ? it->second : "";
}