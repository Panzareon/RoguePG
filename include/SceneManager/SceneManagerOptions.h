#ifndef SCENEMANAGEROPTIONS_H
#define SCENEMANAGEROPTIONS_H

#include "SceneManager.h"
#include "Controller/Configuration.h"

class SceneManagerOptions : public SceneManager
{
    public:
        SceneManagerOptions();
        virtual ~SceneManagerOptions();

        virtual void Tick();
        virtual bool IsFinished();

        virtual void Keybindings();
        virtual void Close();
        virtual void SoundOptions();
        virtual void SetKey(Configuration::Keys key);

        virtual void ChangeMusic();
        virtual void ChangeSfx();

    protected:
        void SetMusicRect();
        void SetSfxRect();

        float m_menuWidth;
        Configuration::Keys m_updateKey;
        bool m_configKey;
        MenuNode* m_keybindings;

        MenuNode* m_soundOptions;
        sf::RectangleShape* m_musicRect;
        sf::RectangleShape* m_sfxRect;

        float m_soundOptionWidth;

        bool m_changeMusic;
        bool m_changeSfx;

        bool m_finished;

    private:
};

#endif // SCENEMANAGEROPTIONS_H
