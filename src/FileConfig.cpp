#include "FileConfig.h"
#include <fstream>
#include <cstdio>


std::string trim(std::string& str)
{
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last-first+1));
}

FileConfig::FileConfig()
{
    //ctor
}

FileConfig::~FileConfig()
{
    //dtor
}

void FileConfig::UpdateKey(std::string key, std::string value, bool safeToFile)
{
    m_values[key] = value;
    if(safeToFile)
    {
        const char* tmp = "data/temp.txt";
        //safe to file
        std::ifstream in(m_filename);
        std::ofstream out(tmp);
        out.seekp(std::ios::beg);
        std::string line;
        while(std::getline(in,line))
        {
            std::size_t found = line.find('=');
            if(found != std::string::npos)
            {
                std::string k = line.substr(0,found);
                k = trim(k);
                if(k == key)
                {
                    line = key + " = " + value;
                }
            }
            out << line << std::endl;
        }
        in.close();
        out.close();
        std::ifstream src(tmp);
        std::ofstream dest(m_filename);
        dest << src.rdbuf();
        src.close();
        std::remove(tmp);
    }
}

void FileConfig::LoadFromFile(std::string filename)
{
    //Parse the file
    m_filename = filename;
    std::ifstream in(filename);
    std::string line;
    std::string commentStart("//");
    while(std::getline(in,line))
    {
        if(line.compare(commentStart) > 0)
        {
            std::size_t found = line.find('=');
            if(found != std::string::npos)
            {
                //got actual value pair
                std::string key = line.substr(0,found);
                key = trim(key);
                std::string value = line.substr(found + 1);
                value = trim(value);
                m_values[key] = value;
            }
        }
    }
}

std::string FileConfig::GetString(std::string key)
{
    //Get value
    auto it = m_values.find(key);
    if(it != m_values.end())
    {
        return it->second;
    }

    //If not found return given string
    return key;
}
