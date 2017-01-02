#ifndef SCENEMANAGERGAMEMENU_H
#define SCENEMANAGERGAMEMENU_H

#include "SceneManager.h"

/*
Class to display the ingame menu
*/
class SceneManagerGameMenu : public SceneManager
{
    public:
        SceneManagerGameMenu(sf::RenderTarget * target, int windowWidth, int windowHeight);
        virtual ~SceneManagerGameMenu();

        //returns true if Scene Manager below should be displayed first
        virtual bool IsTransparent();
        //returns true if Tick should be called for the Scene Manager below
        virtual bool PausesSceneManagerBelow();

    protected:

    private:
};

#endif // SCENEMANAGERGAMEMENU_H
