#include "MusicController.h"
#include "InvalidArgumentException.h"

MusicController* MusicController::m_instance = nullptr;

MusicController::MusicController()
{
    //ctor
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
    }
}
