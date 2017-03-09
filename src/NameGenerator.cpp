#include "NameGenerator.h"

#include <iostream>

NameGenerator* NameGenerator::m_instance = nullptr;

NameGenerator::NameGenerator()
{
    //ctor
    LoadFromFile("data/letter_chances.txt");
    std::string key, value;
    for(auto it = m_values.begin(); it != m_values.end(); it++)
    {
        key = it->first;
        value = it->second;
        try
        {
            if(key.size() == 1)
            {
                m_first[key.at(0)] = std::stof(value);
            }
            if(key.size() == 2)
            {
                m_second[key.at(0)][key.at(1)] = std::stof(value);
            }
            if(key.size() == 3)
            {
                m_third[key.at(0)][key.at(1)][key.at(2)] = std::stof(value);
            }
        }
        catch(...)
        {
            std::cout << "Could not convert " << value << std::endl;
        }
    }
}

NameGenerator::~NameGenerator()
{
    //dtor
}

std::string NameGenerator::GetName(int minLength, int maxLength)
{
    std::string ret;
    for(int i = 0; i < maxLength; i++)
    {
        if(!AddLetterToString(ret, i >= minLength))
        {
            return ret;
        }
    }
    return ret;
}

bool NameGenerator::AddLetterToString(std::string & s, bool canEnd)
{
    bool ok = false;
    while(!ok)
    {
        if(s.size() == 0)
        {
            float chance = ((float)rand()) / RAND_MAX;
            for(auto it = m_first.begin(); it != m_first.end(); it++)
            {
                chance -= it->second;
                if(chance < 0.0f)
                {
                    s.push_back(it->first);
                    ok = true;
                    break;
                }
            }
        }
        else if(s.size() == 1)
        {
            float chance = ((float)rand()) / RAND_MAX;
            unsigned char f = s.at(0);
            for(auto it = m_second[f].begin(); it != m_second[f].end(); it++)
            {
                chance -= it->second;
                if(chance < 0.0f)
                {
                    s.push_back(it->first);
                    ok = true;
                    break;
                }
            }
        }
        else
        {
            float chance = ((float)rand()) / RAND_MAX;
            unsigned char f = s.at(s.size() - 2);
            unsigned char second = s.at(s.size() - 1);
            for(auto it = m_third[f][second].begin(); it != m_third[f][second].end(); it++)
            {
                chance -= it->second;
                if(chance < 0.0f)
                {
                    s.push_back(it->first);
                    ok = true;
                    break;
                }
            }
        }
        if(!ok && canEnd)
        {
            return false;
        }
    }
    return true;
}



NameGenerator* NameGenerator::GetInstance()
{
    if(m_instance == nullptr)
        m_instance = new NameGenerator();
    return m_instance;
}
