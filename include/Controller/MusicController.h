#ifndef MUSICCONTROLLER_H
#define MUSICCONTROLLER_H


#include "SFML/Audio/Music.hpp"

class MusicController
{
    public:
        enum MusicFiles
        {
            Cave
        };

        virtual ~MusicController();

        void PlayMusic(MusicFiles music);

        static MusicController* GetInstance();

        void PauseMusic(bool pause);

        float GetVolume();
        void SetVolume(float volume);
        void SetVolume();

    protected:
        float m_volume;
        sf::Music m_music;
        bool m_pause;

        std::string GetFile(MusicFiles music);

    private:
        static MusicController* m_instance;
        MusicController();
};

#endif // MUSICCONTROLLER_H
