#ifndef SCENEMANAGERGAMEMENU_H
#define SCENEMANAGERGAMEMENU_H

#include "SceneManager.h"

class PartyMember;
/*
Class to display the ingame menu
*/
class SceneManagerGameMenu : public SceneManager
{
    public:
        SceneManagerGameMenu(sf::RenderTarget * target, int windowWidth, int windowHeight);
        virtual ~SceneManagerGameMenu();

        virtual void OpenEquipment();
        virtual void Quit();
        virtual void SelectMember(PartyMember* member);

        virtual void Tick();
        virtual bool IsFinished();

        //returns true if Scene Manager below should be displayed first
        virtual bool IsTransparent();
        //returns true if Tick should be called for the Scene Manager below
        virtual bool PausesSceneManagerBelow();

    protected:
        bool m_finished;

        MenuNode* m_equipmentMenu;

        PartyMember* m_selectedMember;

    private:
};

#endif // SCENEMANAGERGAMEMENU_H
