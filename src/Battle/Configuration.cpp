#include "Controller/Configuration.h"
#include <iostream>
#include "Exception/InvalidArgumentException.h"
#include "Controller/Localization.h"

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

    LoadFromFile("data/config.txt");


    //keyconfig
    m_keys.resize(KEYS_END);
    m_defaultKeys.resize(KEYS_END);
    try
    {
        m_keys.at(MoveUp) = (sf::Keyboard::Key) std::stoi(GetString(KeyToString(MoveUp)));
    }
    catch(...)
    {
        m_keys.at(MoveUp) = sf::Keyboard::Up;
    }
    try
    {
        m_keys.at(MoveDown) = (sf::Keyboard::Key) std::stoi(GetString(KeyToString(MoveDown)));
    }
    catch(...)
    {
        m_keys.at(MoveDown) = sf::Keyboard::Down;
    }
    try
    {
        m_keys.at(MoveRight) = (sf::Keyboard::Key) std::stoi(GetString(KeyToString(MoveRight)));
    }
    catch(...)
    {
        m_keys.at(MoveRight) = sf::Keyboard::Right;
    }
    try
    {
        m_keys.at(MoveLeft) = (sf::Keyboard::Key) std::stoi(GetString(KeyToString(MoveLeft)));
    }
    catch(...)
    {
        m_keys.at(MoveLeft) = sf::Keyboard::Left;
    }
    try
    {
        m_keys.at(Accept) = (sf::Keyboard::Key) std::stoi(GetString(KeyToString(Accept)));
    }
    catch(...)
    {
        m_keys.at(Accept) = sf::Keyboard::Return;
    }
    try
    {
        m_keys.at(Cancel) = (sf::Keyboard::Key) std::stoi(GetString(KeyToString(Cancel)));
    }
    catch(...)
    {
        m_keys.at(Cancel) = sf::Keyboard::Escape;
    }
    try
    {
        m_keys.at(Minimap) = (sf::Keyboard::Key) std::stoi(GetString(KeyToString(Minimap)));
    }
    catch(...)
    {
        m_keys.at(Minimap) = sf::Keyboard::M;
    }
    try
    {
        m_wallTransparency = std::stof(GetString("wall_transparency")) / 100.0f;
        if(m_wallTransparency < 0.0f || m_wallTransparency > 1.0f)
            m_wallTransparency = 0.8f;
    }
    catch(...)
    {
        m_wallTransparency = 0.8f;
    }


    m_defaultKeys.at(MoveDown) = sf::Keyboard::Down;
    m_defaultKeys.at(MoveUp) = sf::Keyboard::Up;
    m_defaultKeys.at(MoveRight) = sf::Keyboard::Right;
    m_defaultKeys.at(MoveLeft) = sf::Keyboard::Left;
    m_defaultKeys.at(Accept) = sf::Keyboard::Return;
    m_defaultKeys.at(Cancel) = sf::Keyboard::Escape;
    m_defaultKeys.at(Minimap) = sf::Keyboard::M;

    m_maxPartySize = 3;
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

sf::Keyboard::Key Configuration::GetDefaultKey(Keys key)
{
    return m_defaultKeys.at(key);
}

int Configuration::GetNumberKeys()
{
    return m_keys.size();
}

void Configuration::ResetLastKey()
{
    m_lastPressed = sf::Keyboard::Unknown;
}

void Configuration::SetLastKeyPressed(sf::Keyboard::Key key)
{
    m_lastPressed = key;
}

sf::Keyboard::Key Configuration::GetLastKey()
{
    return m_lastPressed;
}

bool Configuration::SetKeyConfig(Keys key, sf::Keyboard::Key toSet)
{
    for(int i = 0; i < (int)KEYS_END; i++)
    {
        if((m_keys.at(i) == toSet || m_defaultKeys.at(i) == toSet) && (Keys)i != key)
        {
            return false;
        }
    }
    m_keys.at(key) = toSet;
    UpdateKey(KeyToString(key), std::to_string((int)toSet), true);
    return true;
}

int Configuration::GetMaxPartySize()
{
    return m_maxPartySize;
}

std::string Configuration::KeyToString(Keys key)
{
    switch(key)
    {
    case MoveUp:
        return "move_up";
    case MoveDown:
        return "move_down";
    case MoveRight:
        return "move_right";
    case MoveLeft:
        return "move_left";
    case Accept:
        return "accept";
    case Cancel:
        return "cancel";
    case Minimap:
        return "minimap";
    }
}

std::string Configuration::KeyToString(sf::Keyboard::Key key)
{
    if(key >= sf::Keyboard::A && key <= sf::Keyboard::Z)
    {
        char c = 'A' + (char)key;
        return std::string(&c);
    }
    else
    {
        return Localization::GetInstance()->GetLocalization(std::string("menu.keyBindings.") + std::to_string((int)key));
    }
}

float Configuration::GetWallTransparency()
{
    return m_wallTransparency;
}

void Configuration::SetMusicVolume(float volume)
{
    UpdateKey("music_volume", std::to_string(volume), true);
}

void Configuration::SetSfxVolume(float volume)
{
    UpdateKey("sfx_volume", std::to_string(volume), true);
}

float Configuration::GetMusicVolume()
{
    try
    {
        float retval = std::stof(GetString("music_volume"));
        if(retval >= 0.0f && retval <= 100.0f)
            return retval;
        else
            return 50.0f;
    }
    catch(...)
    {
        return 50.0f;
    }
}

float Configuration::GetSfxVolume()
{
    try
    {
        float retval = std::stof(GetString("sfx_volume"));
        if(retval >= 0.0f && retval <= 100.0f)
            return retval;
        else
            return 50.0f;
    }
    catch(...)
    {
        return 50.0f;
    }
}

bool Configuration::ShowMinimap()
{
    return m_showMinimap;
}

void Configuration::ShowMinimap(bool show)
{
    m_showMinimap = show;
}
