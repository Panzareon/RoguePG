#include "Configuration.h"
#include <iostream>

Configuration* Configuration::m_instance = 0;

Configuration::Configuration()
{
    //ctor
    if(!m_font.loadFromFile("font/arial.ttf"))
        std::cout << "Could not load font!";

    //Default keyconfig:
    //TODO: load from file
    m_moveUp = sf::Keyboard::Up;
    m_moveDown = sf::Keyboard::Down;
    m_moveRight = sf::Keyboard::Right;
    m_moveLeft = sf::Keyboard::Left;
    m_accept = sf::Keyboard::Space;
    m_cancel = sf::Keyboard::Delete;

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

sf::Keyboard::Key Configuration::GetMoveUpKey()
{
    return m_moveUp;
}

sf::Keyboard::Key Configuration::GetMoveDownKey()
{
    return m_moveDown;
}

sf::Keyboard::Key Configuration::GetMoveRightKey()
{
    return m_moveRight;
}

sf::Keyboard::Key Configuration::GetMoveLeftKey()
{
    return m_moveLeft;
}

sf::Keyboard::Key Configuration::GetAcceptKey()
{
    return m_accept;
}

sf::Keyboard::Key Configuration::GetCancelKey()
{
    return m_cancel;
}


int Configuration::GetMaxPartySize()
{
    return m_maxPartySize;
}
