#ifndef SOUNDCONTROLLER_H
#define SOUNDCONTROLLER_H

#include <vector>
#include <map>
#include "SFML/Audio/Sound.hpp"
#include "SFML/Audio/SoundBuffer.hpp"

class SoundController
{
    public:
        enum Sounds{
            Hit, Wind, Water, Earth, Fire
        };

        virtual ~SoundController();

        static SoundController* GetInstance();

        sf::SoundBuffer * GetBuffer(Sounds sound);

        void PlaySound(Sounds sound);

        void PlaySound(Sounds sound, int soundIndex);


        float GetVolume();
        void SetVolume(float volume);

    protected:
        float m_volume;

        std::vector<sf::Sound> m_sounds;

        std::map<Sounds, sf::SoundBuffer> m_soundBuffer;



    private:

        SoundController();
        static SoundController* m_instance;

};

#endif // SOUNDCONTROLLER_H
