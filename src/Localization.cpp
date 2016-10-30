#include "Localization.h"
#include "fstream"


std::string trim(std::string& str)
{
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last-first+1));
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

