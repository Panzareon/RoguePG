#ifndef SCENEMANAGERMAINMENU_H
#define SCENEMANAGERMAINMENU_H

#include "SceneManager.h"

class SceneManagerMainMenu : public SceneManager
{
    public:
        SceneManagerMainMenu(sf::RenderTarget * target, int windowWidth, int windowHeight);
        virtual ~SceneManagerMainMenu();

        virtual void StartDungeon();
        virtual void Quit();

        virtual void Tick();
        virtual bool IsFinished();
    protected:


    private:
};

#endif // SCENEMANAGERMAINMENU_H
