#include "MusicController.h"
#include "InvalidArgumentException.h"
#include "Configuration.h"

MusicController* MusicController::m_instance = nullptr;

MusicController::MusicController()
{
    //ctor
    m_pause = false;
    m_volume = Configuration::GetInstance()->GetMusicVolume();
}

MusicController::~MusicController()
{
    //dtor
}

void MusicController::PlayMusic(MusicFiles music)
{
    std::string file =  GetFile(music);
    if(!m_music.openFromFile(file))
    {
        std::string msg("Could not load file: ");
        msg += file;
        throw InvalidArgumentException(msg);
    }
    m_music.setLoop(true);
    if(!m_pause)
    {
        m_music.play();
        SetVolume();
    }
}

std::string MusicController::GetFile(MusicFiles music)
{
    switch(music)
    {
    case Cave:
        return "music/cave.ogg";
    }
}

MusicController* MusicController::GetInstance()
{
    if(m_instance == nullptr)
        m_instance = new MusicController();
    return m_instance;
}


void MusicController::PauseMusic(bool pause)
{
    m_pause = pause;
    if(pause)
    {
        m_music.pause();
    }
    else
    {
        m_music.play();
        SetVolume();
    }
}

float MusicController::GetVolume()
{
    return m_volume;
}

void MusicController::SetVolume(float volume)
{
    if(volume >= 0.0f && volume <= 100.0f)
    {
        m_volume = volume;
    }
    SetVolume();
}

void MusicController::SetVolume()
{
    m_music.setVolume(m_volume);
}
