#include "Localization.h"
#include "fstream"
#include <sstream>

std::string trim(std::string& str)
{
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last-first+1));
}

std::string format(std::string& str, std::vector<float>* values)
{
    std::stringstream out;
    out.precision(2);
    size_t pos;
    while (pos != str.npos)
    {
        pos = str.find_first_of('%');
        if(pos == str.npos)
        {
            out << str;
        }
        else
        {
            out << str.substr(0,pos);
            //only check for one digit numbers
            char next = str.at(pos + 1);
            if(next >= '0' && next <= '9')
            {
                //check what number should be displayed here
                next -= '0';
                if(values->size() > next)
                {
                    //Check if it should be formated as percent ("%0%" with value 0.5 to "50%")
                    if(str.at(pos + 2) == '%')
                    {
                        out << values->at(next) * 100.0f << "%";
                    }
                    else if(str.at(pos + 2) == '/')
                    {
                        out << (1.0f / values->at(next)) * 100.0f << "%";
                        str.erase(0, 1);
                    }
                    else
                    {
                        out << values->at(next);
                    }
                }
            }
            str.erase(0, pos + 2);
        }
    }
    return out.str();
}

std::string formatWithStrings(std::string& str, std::vector<std::string>* values)
{
    std::stringstream out;
    out.precision(2);
    size_t pos;
    while (pos != str.npos)
    {
        pos = str.find_first_of('%');
        if(pos == str.npos)
        {
            out << str;
        }
        else
        {
            out << str.substr(0,pos);
            //only check for one digit numbers
            char next = str.at(pos + 1);
            if(next >= '0' && next <= '9')
            {
                //check what number should be displayed here
                next -= '0';
                if(values->size() > next)
                {
                    out << values->at(next);
                }
            }
            str.erase(0, pos + 2);
        }
    }
    return out.str();
}

Localization* Localization::m_instance = nullptr;

Localization::Localization()
{
    //ctor
    //TODO: Get selected language
    LoadLocalizationFile("data/localization_en.txt", English);
}

Localization::~Localization()
{
    //dtor
}

Localization* Localization::GetInstance()
{
    if(m_instance == nullptr)
        m_instance = new Localization();
    return m_instance;
}

std::string Localization::GetLocalization(std::string toLocalize)
{
    //Get Translation
    auto it = m_localization.find(toLocalize);
    if(it != m_localization.end())
    {
        return it->second;
    }

    //If not found return unlocalized string
    return toLocalize;
}

//returns formatted string
std::string Localization::GetLocalizationWithFloats(std::string toLocalize, std::vector<float>* values)
{
    std::string str = GetLocalization(toLocalize);
    return format(str, values);
}

//returns formatted string
std::string Localization::GetLocalizationWithStrings(std::string toLocalize, std::vector<std::string>* values)
{
    std::string str = GetLocalization(toLocalize);
    return formatWithStrings(str, values);
}

void Localization::LoadLocalizationFile(std::string filename, Languages language)
{
    m_localization.clear();
    m_language = language;
    //Parse the localization file
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
                m_localization[key] = value;
            }
        }
    }
}

