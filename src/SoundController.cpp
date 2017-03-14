#include "SoundController.h"
#include "Configuration.h"

SoundController* SoundController::m_instance = nullptr;

SoundController::SoundController()
{
    //ctor
    m_volume = Configuration::GetInstance()->GetSfxVolume();
}

SoundController::~SoundController()
{
    //dtor
}

SoundController* SoundController::GetInstance()
{
    if(m_instance == nullptr)
        m_instance = new SoundController();
    return m_instance;
}

sf::SoundBuffer* SoundController::GetBuffer(Sounds sound)
{
    auto it = m_soundBuffer.find(sound);
    if(it == m_soundBuffer.end())
    {
        sf::SoundBuffer* buffer = &m_soundBuffer[sound];
        switch(sound)
        {
        case Hit:
            buffer->loadFromFile("sfx/hit.wav");
            break;
        case Wind:
            buffer->loadFromFile("sfx/wind.wav");
            break;
        case Earth:
            buffer->loadFromFile("sfx/stone.wav");
            break;
        case Water:
            buffer->loadFromFile("sfx/water.wav");
            break;
        case Fire:
            buffer->loadFromFile("sfx/fire.wav");
            break;
        }
        return buffer;
    }
    else
    {
        return &(it->second);
    }
}

void SoundController::PlaySound(Sounds sound)
{
    bool newSound = true;
    for(int i = 0; i < m_sounds.size(); i++)
    {
        if(m_sounds[i].getStatus() == sf::Sound::Stopped)
        {
            PlaySound(sound, i);
            newSound = false;
            break;
        }
    }
    if(newSound)
    {
        PlaySound(sound, m_sounds.size());
    }
}

void SoundController::PlaySound(Sounds sound, int soundIndex)
{
    sf::SoundBuffer* buffer = GetBuffer(sound);
    if(m_sounds.size() <= soundIndex)
    {
        m_sounds.resize(soundIndex + 1);
    }
    m_sounds[soundIndex].setBuffer(*buffer);
    m_sounds[soundIndex].play();
    m_sounds[soundIndex].setVolume(m_volume);
}

float SoundController::GetVolume()
{
    return m_volume;
}

void SoundController::SetVolume(float volume)
{
    if(volume >= 0.0f && volume <= 100.0f)
    {
        m_volume = volume;
    }
}
