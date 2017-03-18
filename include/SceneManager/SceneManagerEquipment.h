#ifndef SCENEMANAGEREQUIPMENT_H
#define SCENEMANAGEREQUIPMENT_H

#include "SceneManager.h"
#include "Controller/Enums.h"
#include "SceneGraph/MenuNodeItems.h"
#include "SceneGraph/TextNode.h"
#include "AttributeNodesDisplay.h"
#include <map>

class PartyMember;
class Equipment;

class SceneManagerEquipment : AttributeNodesDisplay, public SceneManager
{
    public:
        SceneManagerEquipment();
        virtual ~SceneManagerEquipment();

        virtual void Tick();
        virtual bool IsFinished();

        virtual void SelectMember(PartyMember* member);
        virtual void SelectEquipment(Equipment* equipment);
        virtual void Equip(Equipment* equipment);
        virtual void SelectEquipmentSkills(bool selected);
        virtual void SelectSkill(Skill* skill);


        //returns true if Scene Manager below should be displayed first
        virtual bool IsTransparent();
        //returns false if Tick should be called for the Scene Manager below
        virtual bool PausesSceneManagerBelow();

    protected:
        void UpdateMemberStats();
        void RemoveEquipmentSkillMenu();
        void SetEquipmentSkillMenu(Equipment* equipment);

        MenuNode* m_mainMenu;
        Node* m_equipmentSkillBase;
        MenuNodeItems<Equipment>* m_equipmentItems;
        MenuNodeItems<Skill>* m_equipmentSkills;
        sf::RectangleShape* m_equipmentSkillLearned;
        sf::RectangleShape* m_equipmentSkillLearning;
        Node* m_equipmentSkillLearningNode;
        bool m_equipmentSkillsSelected;

        bool m_finished;

        TextNode* m_equipmentDescription;

        //For Equipment menu
        Equipment* m_selectedEquipment;
        int m_maxShownHeroes;
        PartyMember* m_selectedMember;
        std::map<BattleEnums::Attribute, int> m_memberStats;

        Node* m_background;

    private:
};

#endif // SCENEMANAGEREQUIPMENT_H
