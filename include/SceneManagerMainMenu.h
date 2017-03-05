#ifndef SCENEMANAGERMAINMENU_H
#define SCENEMANAGERMAINMENU_H

#include "SceneManager.h"
#include "Configuration.h"

class SceneManagerMainMenu : public SceneManager
{
    public:
        SceneManagerMainMenu(sf::RenderTarget * target, int windowWidth, int windowHeight);
        virtual ~SceneManagerMainMenu();

        virtual void StartDungeon();
        virtual void Quit();
        virtual void Keybindings();
        virtual void SetKey(Configuration::Keys key);

        virtual void Tick();
        virtual bool IsFinished();
    protected:

        Configuration::Keys m_updateKey;
        bool m_configKey;
        MenuNode* m_keybindings;


    private:
};

#endif // SCENEMANAGERMAINMENU_H
