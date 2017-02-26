#ifndef SCENEMANAGERGAMEMENU_H
#define SCENEMANAGERGAMEMENU_H

#include "MenuNodeItems.h"
#include "SceneManager.h"
#include "Enums.h"
#include "TextNode.h"
#include <map>

class PartyMember;
class Equipment;
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
        virtual void SelectEquipment(Equipment* equipment);
        virtual void Equip(Equipment* equipment);

        virtual void Tick();
        virtual bool IsFinished();

        //returns true if Scene Manager below should be displayed first
        virtual bool IsTransparent();
        //returns true if Tick should be called for the Scene Manager below
        virtual bool PausesSceneManagerBelow();

    protected:
        void UpdateMemberStats();

        bool m_finished;

        MenuNode* m_equipmentMenu;
        MenuNodeItems<Equipment>* m_equipmentItems;

        std::vector<std::map<BattleEnums::Attribute, TextNode*>> m_attributeNodes;
        std::map<BattleEnums::Attribute, std::pair<int,int>> m_attributeNodePosition;

        //For Equipment menu
        int m_maxShownHeroes;
        PartyMember* m_selectedMember;
        std::map<BattleEnums::Attribute, int> m_memberStats;

    private:
};

#endif // SCENEMANAGERGAMEMENU_H
