#include "Configuration.h"
#include <iostream>
#include "InvalidArgumentException.h"

Configuration* Configuration::m_instance = 0;

Configuration::Configuration()
{
    //ctor
    //TODO: get active font from somewhere else
    if(!m_font.loadFromFile("font/arial.ttf"))
    {
        std::string msg("Could not load font!");
        throw InvalidArgumentException(msg);
    }

    //Default keyconfig:
    //TODO: load from file
    int numberOfKeys = 6;
    m_keys.resize(numberOfKeys);
    m_keys.at(MoveUp) = sf::Keyboard::Up;
    m_keys.at(MoveDown) = sf::Keyboard::Down;
    m_keys.at(MoveRight) = sf::Keyboard::Right;
    m_keys.at(MoveLeft) = sf::Keyboard::Left;
    m_keys.at(Accept) = sf::Keyboard::Space;
    m_keys.at(Cancel) = sf::Keyboard::Delete;

    m_maxPartySize = 4;
}

Configuration::~Configuration()
{
    //dtor
}
Configuration* Configuration::GetInstance()
{
    if(m_instance == 0)
        m_instance = new Configuration();
    return m_instance;
}

sf::Font* Configuration::GetFont()
{
    return &m_font;
}

sf::Keyboard::Key Configuration::GetKey(Keys key)
{
    return m_keys.at(key);
}
int Configuration::GetNumberKeys()
{
    return m_keys.size();
}


int Configuration::GetMaxPartySize()
{
    return m_maxPartySize;
}
