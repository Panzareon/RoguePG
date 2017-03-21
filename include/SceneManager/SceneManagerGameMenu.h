#ifndef SCENEMANAGERGAMEMENU_H
#define SCENEMANAGERGAMEMENU_H

#include "SceneManager.h"
/*
Class to display the ingame menu
*/
class SceneManagerGameMenu : public SceneManager
{
    public:
        SceneManagerGameMenu();
        virtual ~SceneManagerGameMenu();

        virtual void Quit();

        virtual void Tick();
        virtual bool IsFinished();

        //returns true if Scene Manager below should be displayed first
        virtual bool IsTransparent();
        //returns false if Tick should be called for the Scene Manager below
        virtual bool PausesSceneManagerBelow();

    protected:

        bool m_finished;

    private:
};

#endif // SCENEMANAGERGAMEMENU_H